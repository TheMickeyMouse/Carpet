def filtergltype(s):
    if s[-1] == '*':
        return filtergltype(s[:-1]) + '*'
    result = (s.replace("GLintptr",   "IntPtr")
               .replace("GLuint",     "Uint")
               .replace("GLhalf",     "Ushort")
               .replace("GLshort",    "Short")
               .replace("GLushort",   "Ushort")
               .replace("GLenum",     "Enum")
               .replace("GLsizeiptr", "IsizePtr")
               .replace("GLsizei",    "Isize")
               .replace("GLfixed",    "Fixed")
               .replace("GLint",      "Int")
               .replace("GLclampx",   "IClamp")
               .replace("GLfloat",    "Float")
               .replace("GLclampf",   "FClamp")
               .replace("GLdouble",   "Double")
               .replace("GLclampd",   "DClamp")
               .replace("GLbyte",     "Byte")
               .replace("GLubyte",    "Ubyte")
               .replace("GLbitfield", "Bitfield")
               .replace("GLboolean",  "Bool")
               .replace("GLchar",     "char")
               .replace("GLvoid",     "void")
               .replace("GLhandleARB","Handle")
               .replace("GLsync",     "Sync")
               .replace("GLvdpauSurfaceNV", "IntPtr")
               .replace("GLeglClientBufferEXT", "ClientBuffer")
               .replace("GLLOGPROCREGAL", "LogFuncREGAL")
               .replace("GLDEBUGPROC",    "LogFunc")
               .replace("GLVULKANPROCNV", "VulkanProc")
               .replace("cl_context", "CLContext")
               .replace("cl_event", "CLEvent")
               .removesuffix("EXT")
               .removesuffix("ARB"))
    return result

def intovalidtype(t, arg):
    if arg[0] == '*':
        return intovalidtype(t + '*', arg[1:])
    if arg[-1] == ']':
        return intovalidtype(t + '*', arg[:arg.find('[')])
    return (t, arg)

entries = {}
subdefines = {}
fout = ""

blacklist = set()
enums = {}
vout = ""
with open("../Dependencies/GLEW/include/GL/glew.h") as f:
    for line in f:
        if line.startswith("#ifndef GL_"):
            blacklist.add(line.removeprefix("#ifndef GL_")[:-1])
            continue
        if line.startswith("#define GL_"):
            name, *val = line.removeprefix("#define GL_")[:-1].split(' ')
            if name in blacklist: continue
            if len(val) != 1 or not val[0].startswith("0x"): continue
            if name[0].isdigit(): name = 'N' + name
            enums[name] = int(val[0][2:].removesuffix("ull").removesuffix("u"), 16)
            continue
        if line.startswith("GLAPI "):
            type, sig = line.removeprefix("GLAPI ").split(' GLAPIENTRY ')
            name, rest = sig[:-3].split(' (')
            name = name.removeprefix("gl")
            if rest == 'void':
                entries[name] = (filtergltype(type), '')
                continue
            argtup = (intovalidtype(s[:(i := s.rfind(' '))].strip(), s[i+1:]) for s in rest.split(','))
            entries[name] = (
                filtergltype(type),
                ''.join(f'({filtergltype(t)})({n})' for t, n in argtup)
            )
            continue
        if line.startswith("#define gl"):
            fname, _ = line.removeprefix("#define gl").split(' ')
            subdefname = f"PFNGL{fname.upper()}PROC"
            fsig = subdefines.get(subdefname)
            if fsig is None:
                print(f"oh yeah {fname} doesnt exist. skipped")
                continue
            entries[fname] = fsig
            del subdefines[subdefname]
        elif line.startswith("typedef "):
            line = line.removeprefix("typedef ")
            s = line.find(' (')
            type = line[:s]
            if line[s+1:].startswith("(GLAPIENTRY * "):
                rest = line[s+1:].removeprefix("(GLAPIENTRY * ")
                name, args = rest.split(") ")
                if args[1:-3] == 'void':
                    subdefines[name] = (filtergltype(type), '')
                    continue
                argtup = (intovalidtype(s[:(i := s.rfind(' '))].strip(), s[i+1:]) for s in args[1:-3].split(','))
                # print(f'parsing {name}')
                subdefines[name] = (filtergltype(type), ''.join(f'({filtergltype(type)})({name})' for type, name in argtup))
            else: continue

    mnamelen, mtypelen = 0, 0
    for n, t in entries.items():
        mnamelen = max(mnamelen, len(n))
        mtypelen = max(mtypelen, len(t[0]))

    indent = False
    for n, r in entries.items():
        nn = f'{n},'
        rt = f'{r[0]},'

        if indent: fout += "    "

        fout += f'M({nn:<{mnamelen+1}}{rt:<{mtypelen+1}}{r[1] if len(r[1]) != 0 else ""}) \\\n'

        indent = True

    mnamelen = 0
    for n, _ in enums.items():
        mnamelen = max(mnamelen, len(n))
    for n, v in enums.items():
        vout += f"        {n:<{mnamelen}} = 0x{v:0X}, \n"

with open('funcs.txt', 'w') as f:
    f.write(fout)
with open("vars.txt", 'w') as f:
    f.write(vout)
