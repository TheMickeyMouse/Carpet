import gdb.printing
import itertools

# TUTORIAL FOR ADDING PRETTY PRINTERS:
# goto the home folder (on windows it's C:/users/$username$
# create a raw '.gdbinit' (thats the name!) file with
# the following as the contents (you may have to use notepad++ to inser this)
# ```
# python
# import sys
# sys.path.append('path/to/a/directory/with_the_pretty_print_file/')
#
# from quasi import register_quasi_printer
# register_quasi_printer()
# ```
# choose the path to put quasi.py (the pretty print file)
# copy this current file to it and rename it to quasi.py
# add an empty __init__.py file
# you're (probably) done!


class BufferPrinterIterator:
    def __init__(self, buf, count):
        self.buf = buf
        self.count = count
        self.i = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.i == self.count:
            raise StopIteration
        self.i += 1
        return f'[{self.i - 1}]', self.buf[self.i - 1]


class QuasiVecPrinter:
    def __init__(self, typename, val):
        self.typename = typename
        self.val = val

    def to_string(self):
        return f'{self.typename} of len {self.val["size"]}, cap {self.val["capacity"]}'

    def children(self):
        return BufferPrinterIterator(self.val['data'], self.val['size'])

    def display_hint(self):
        return 'array'


class QuasiSpanPrinter:
    def __init__(self, typename, val):
        self.typename = typename
        self.val = val

    def to_string(self):
        return f'{self.typename} of len {self.val["size"]}'

    def children(self):
        return BufferPrinterIterator(self.val['data'], self.val['size'])

    def display_hint(self):
        return 'array'


class QuasiArrayPrinter:
    def __init__(self, typename, val):
        self.typename = typename
        self.val = val
        self.n = val.type.template_argument(1)

    def to_string(self):
        return self.typename

    def children(self):
        if self.n == 0:
            return iter(())
        else:
            return BufferPrinterIterator(self.val['array'], self.n)

    def display_hint(self):
        return 'array'


class QuasiOptionPrinter:
    def __init__(self, val):
        self.val = val
        self.some = val.type.template_argument(0)

    def to_string(self):
        return f'Some({self.some})' if self.val['isSome'] else 'None()'

    def children(self):
        if self.val['isSome']:
            yield 'Some', self.val['value']
        return

class QuasiOptionUsizePrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return f'Some({self.val["value"]})' if self.val['value'] != 0xFFFF_FFFF_FFFF_FFFF else 'None()'


class QuasiRefPrinter:
    def __init__(self, typename, val):
        self.typename = typename
        self.val = val

    def to_string(self):
        return self.typename

    def children(self):
        yield 'Ref', self.val['obj'].dereference()


class QuasiOptRefPrinter:
    def __init__(self, val):
        self.val = val
        self.some = val.type.template_argument(0)

    def to_string(self):
        return f'Some({self.some}&)' if self.val['obj'] else 'None()'

    def children(self):
        if self.val['obj']:
            yield 'Some', self.val['obj']
        return


class QuasiBoxPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return f'Box({self.val["data"]})' if self.val['data'] else 'nullptr'

    def children(self):
        if self.val['data']:
            yield '*', self.val['data']
        return


class QuasiArrayBoxPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return f'ArrayBox({self.val["buf"]}, len={self.val["size"]})' if self.val['buf'] else 'nullptr'

    def children(self):
        return BufferPrinterIterator(self.val['buf'], self.val['size'])

    def display_hint(self):
        return 'array'


class QuasiStringPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        s = self.val['small']
        small = int(s['sizePackedFlag'] & 1) == 0
        string = s if small else self.val['large']
        return string['data'].lazy_string(length=(string['sizePackedFlag'] >> 1))

    def display_hint(self):
        return 'string'


class QuasiStrPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return self.val['data'].lazy_string(length=self.val['size'])

    def display_hint(self):
        return 'string'


class QuasiRangePrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        return f'[{self.val["min"]},{self.val["max"]})'

    def children(self):
        yield 'min', self.val['min']
        yield 'max', self.val['max']

class QuasiTuplePrinter:
    def __init__(self, typename, val):
        self.representation = typename[6:-1]
        self.val = val

    def to_string(self):
        return f'({self.representation})'

    def children(self):
        i = 0
        head = self.val
        while True:
            yield f'.{i}', head['first']
            if len(head.fields()) == 0: break
            head = head['rest']


class QuasiVariantPrinter:
    def __init__(self, val):
        self.val = val
        self.type = val.type

    def to_string(self):
        return f'{self.type.template_argument(self.val["tag"])}'

    def children(self):
        yield '*', self.val.cast(self.type.template_argument(self.val['tag']).reference())

class QuasiHashTablePrinter:
    def __init__(self, val):
        self.val = val
        t = val.type
        self.key = t.template_argument(1)
        self.value = t.template_argument(2)

    def to_string(self):
        if self.value.tag != gdb.TYPE_CODE_VOID:
            return f'HashMap<{self.key}, {self.value}> with {self.val["elmCount"]} elements'
        else:
            return f'HashSet<{self.key}> with {self.val["elmCount"]} elements'

    def children(self):
        info, kv = self.val['infoData'], self.val['kvData']
        end = info.reinterpret_cast(kv.type)
        byteptrt = gdb.lookup_type('uint64_t').pointer()
        for _ in range(self.val['elmCount']):
            n = int(info.reinterpret_cast(byteptrt).dereference())
            while n == 0:
                info += 8
                kv += 8
                n = int(info.reinterpret_cast(byteptrt).dereference())

            n = int(info.reinterpret_cast(byteptrt).dereference())
            # n = (((n << 56) & 0xFF00000000000000) |
            #      ((n << 40) & 0x00FF000000000000) |
            #      ((n << 24) & 0x0000FF0000000000) |
            #      ((n <<  8) & 0x000000FF00000000) |
            #      ((n >>  8) & 0x00000000FF000000) |
            #      ((n >> 24) & 0x0000000000FF0000) |
            #      ((n >> 40) & 0x000000000000FF00) |
            #      ((n >> 56) & 0x00000000000000FF))

            inc = ((n & -n).bit_length() - 1) // 8
            kv += inc
            info += inc
            node = kv.dereference()['data']
            if node.type.tag == gdb.TYPE_CODE_PTR:
                node = node.dereference()

            if self.value.tag != gdb.TYPE_CODE_VOID:
                yield f'[{node["key"]}]', node["value"]
            else:
                yield f'[{node["key"]}]', ()
            info += 1
            kv += 1
    #
    # def display_hint(self):
    #     return 'map'

class QuasiMathVecPrinter:
    def __init__(self, val):
        self.val = val
        self.n = int(val.type.template_argument(1))

    def to_string(self):
        return f'({", ".join(str(self.val[x]) for x in "xyzw"[:self.n])})'

    def children(self):
        for x in "xyzw"[:self.n]:
            yield x, self.val[x]

class QuasiMathMatrixPrinter:
    def __init__(self, val):
        self.val = val
        self.n = int(val.type.template_argument(0))
        self.m = int(val.type.template_argument(1))

    def children(self):
        u = self.val['unitVectors']
        for i in range(self.n):
            yield f'{"ijkl"[i]}hat', u[i]

    def display_hint(self):
        return 'array'

def quasi_lookup(val):
    lookup: str = val.type.tag
    if lookup is None:
        return None
    if not lookup.startswith('Quasi::'):
        return None
    lookup = lookup[7:]
    last = lookup.find('<')
    last = len(lookup) if last == -1 else last
    match lookup[:last]:
        case 'Vec':         return QuasiVecPrinter      (lookup, val)
        case 'Span':        return QuasiSpanPrinter     (lookup, val)
        case 'Array':       return QuasiArrayPrinter    (lookup, val)
        case 'Option':      return QuasiOptionPrinter   (val)
        case 'OptionUsize': return QuasiOptionUsizePrinter   (val)
        case 'Ref':         return QuasiRefPrinter      (lookup, val)
        case 'OptRef':      return QuasiOptRefPrinter   (val)
        case 'Box':         return QuasiBoxPrinter      (val)
        case 'ArrayBox':    return QuasiArrayBoxPrinter (val)
        case 'String':      return QuasiStringPrinter   (val)
        case 'Str':         return QuasiStrPrinter      (val)
        case 'CStr':        return QuasiStrPrinter      (val)
        case 'Range':       return QuasiRangePrinter    (val)
        case 'Tuple':       return QuasiTuplePrinter    (lookup, val)
        case 'Variant':     return QuasiVariantPrinter  (val)
        case 'HashTable':   return QuasiHashTablePrinter(val)
        case 'Math::Vector':     return QuasiMathVecPrinter(val)
        case 'Math::Matrix':     return QuasiMathMatrixPrinter(val)
    return None


def register_quasi_printer():
    obj = gdb.current_objfile()
    if obj is None:
        obj = gdb
    obj.pretty_printers.append(quasi_lookup)
