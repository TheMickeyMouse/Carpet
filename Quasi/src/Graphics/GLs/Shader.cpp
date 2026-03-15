#include "Shader.h"

#include <glp.h>
#include "Texture.h"
#include "Utils/Text.h"
#include "GLDebug.h"
#include "Utils/Iter/LinesIter.h"

namespace Quasi::Graphics {
    Shader::Shader(GraphicsID id) : ShaderProgram(id) {}

    ShaderProgram::ShaderProgram(GraphicsID id) : GLObject(id) {}

    ShaderProgram ShaderProgram::New(Str program) {
        const auto [vtx, frg, geo] = ParseShader(program);
        const GraphicsID rendererID = CreateShader(vtx, frg, geo);
        return ShaderProgram { rendererID };
    }

    ShaderProgram ShaderProgram::New(Str vert, Str frag, Str geom) {
        const GraphicsID rendererID = CreateShader(vert, frag, geom);
        return ShaderProgram { rendererID };
    }

    ShaderProgram ShaderProgram::NewCompute(Str program) {
        const GraphicsID rendererID = CreateShaderCompute(program);
        return ShaderProgram { rendererID };
    }

    void ShaderProgram::DestroyObject(GraphicsID id) {
        QGLCall$(GL::DeleteProgram(id));
    }

    void ShaderProgram::BindObject(GraphicsID id) {
        QGLCall$(GL::UseProgram(id));
    }

    void ShaderProgram::UnbindObject() {
        QGLCall$(GL::UseProgram(0));
    }

    int ShaderProgram::GetUniformLocation(CStr name) const {
        return QGLCall$(GL::GetUniformLocation(rendererID, name.Data()));
    }

    int Shader::GetUniformLocation(CStr name) {
        if (const auto cachedLoc = uniformCache.Get(name))
            return *cachedLoc;

        const int location = ShaderProgram::GetUniformLocation(name);
        GLLogger().Assert(location != -1, "invalid uniform location for '{}'", name);
        uniformCache[String { name }] = location;
        return location;
    }

    void Shader::SetUniformDyn(CStr name, ShaderUniformType type, Bytes data) {
        using enum ShaderUniformType;
        switch (type) {
            case F_UNIT:    return SetUniformFloat(name, data.ReadFirst<float>());
            case FV2:       return SetUniformFv2  (name, data.ReadFirst<Math::fv2>());
            case FV3:       return SetUniformFv3  (name, data.ReadFirst<Math::fv3>());
            case FV4:       return SetUniformFv4  (name, data.ReadFirst<Math::fv4>());
            case F_ARRAY:   return SetUniformFloatArr(name, data.Transmute<float>());
            case FV2_ARRAY: return SetUniformFv2Arr  (name, data.Transmute<Math::fv2>());
            case FV3_ARRAY: return SetUniformFv3Arr  (name, data.Transmute<Math::fv3>());
            case FV4_ARRAY: return SetUniformFv4Arr  (name, data.Transmute<Math::fv4>());
            case I_UNIT:    return SetUniformInt   (name, data.ReadFirst<int>());
            case IV2:       return SetUniformIv2   (name, data.ReadFirst<Math::iv2>());
            case IV3:       return SetUniformIv3   (name, data.ReadFirst<Math::iv3>());
            case IV4:       return SetUniformIv4   (name, data.ReadFirst<Math::iv4>());
            case I_ARRAY:   return SetUniformIntArr(name, data.Transmute<int>());
            case IV2_ARRAY: return SetUniformIv2Arr(name, data.Transmute<Math::iv2>());
            case IV3_ARRAY: return SetUniformIv3Arr(name, data.Transmute<Math::iv3>());
            case IV4_ARRAY: return SetUniformIv4Arr(name, data.Transmute<Math::iv4>());
            case U_UNIT:    return SetUniformUint(name, data.ReadFirst<uint>());
            case UV2:       return SetUniformUv2 (name, data.ReadFirst<Math::uv2>());
            case UV3:       return SetUniformUv3 (name, data.ReadFirst<Math::uv3>());
            case UV4:       return SetUniformUv4 (name, data.ReadFirst<Math::uv4>());
            case U_ARRAY:   return SetUniformUintArr(name, data.Transmute<uint>());
            case UV2_ARRAY: return SetUniformUv2Arr (name, data.Transmute<Math::uv2>());
            case UV3_ARRAY: return SetUniformUv3Arr (name, data.Transmute<Math::uv3>());
            case UV4_ARRAY: return SetUniformUv4Arr (name, data.Transmute<Math::uv4>());
            case FMAT_2X2:  return SetUniformMat2x2Arr(name, data.Transmute<Math::Matrix2x2>());
            case FMAT_2X3:  return SetUniformMat2x3Arr(name, data.Transmute<Math::Matrix2x3>());
            case FMAT_2X4:  return SetUniformMat2x4Arr(name, data.Transmute<Math::Matrix2x4>());
            case FMAT_3X2:  return SetUniformMat3x2Arr(name, data.Transmute<Math::Matrix3x2>());
            case FMAT_3X3:  return SetUniformMat3x3Arr(name, data.Transmute<Math::Matrix3x3>());
            case FMAT_3X4:  return SetUniformMat3x4Arr(name, data.Transmute<Math::Matrix3x4>());
            case FMAT_4X2:  return SetUniformMat4x2Arr(name, data.Transmute<Math::Matrix4x2>());
            case FMAT_4X3:  return SetUniformMat4x3Arr(name, data.Transmute<Math::Matrix4x3>());
            case FMAT_4X4:  return SetUniformMat4x4Arr(name, data.Transmute<Math::Matrix4x4>());
            default:;
        }
    }

    void Shader::SetUniformArgs(const ShaderArgs& args) {
        Bytes argBytes = args.rawBytes;
        while (argBytes) {
            const ShaderUniformType type = (ShaderUniformType)argBytes.TakeFirst();
            Bytes bytes;
            if (IsArrayUnif(type) || IsMatrixUnif(type)) {
                const usize byteCount = argBytes.Read<usize>();
                bytes = Bytes::Slice(argBytes.Read<const byte*>(), byteCount);
            } else {
                bytes = argBytes.TakeFirst(4 * sizeof(u32));
            }
            const CStr uname = (const char*)argBytes.Data();
            SetUniformDyn(uname, type, bytes);
            argBytes.Advance(uname.LengthWithNull());
        }
    }

    void Shader::SetUniformFloat(CStr name, float x)                 { GL::Uniform1f(GetUniformLocation(name), x); }
    void Shader::SetUniformFv2(CStr name, const Math::fv2& v2s) { GL::Uniform2f(GetUniformLocation(name), v2s.x, v2s.y); }
    void Shader::SetUniformFv3(CStr name, const Math::fv3& v3s) { GL::Uniform3f(GetUniformLocation(name), v3s.x, v3s.y, v3s.z); }
    void Shader::SetUniformFv4(CStr name, const Math::fv4& v4s) { GL::Uniform4f(GetUniformLocation(name), v4s.x, v4s.y, v4s.z, v4s.w); }
    void Shader::SetUniformFloatArr(CStr name, Span<const float> xs) { GL::Uniform1fv(GetUniformLocation(name), xs.Length(), xs.Data()); }
    void Shader::SetUniformFv2Arr(CStr name, Span<const Math::fv2> v2s) { GL::Uniform2fv(GetUniformLocation(name), v2s.Length(), (const float*)v2s.Data()); }
    void Shader::SetUniformFv3Arr(CStr name, Span<const Math::fv3> v3s) { GL::Uniform3fv(GetUniformLocation(name), v3s.Length(), (const float*)v3s.Data()); }
    void Shader::SetUniformFv4Arr(CStr name, Span<const Math::fv4> v4s) { GL::Uniform4fv(GetUniformLocation(name), v4s.Length(), (const float*)v4s.Data()); }
    void Shader::SetUniformInt(CStr name, int x)                     { GL::Uniform1i(GetUniformLocation(name), x); }
    void Shader::SetUniformIv2(CStr name, const Math::iv2& v2s) { GL::Uniform2i(GetUniformLocation(name), v2s.x, v2s.y); }
    void Shader::SetUniformIv3(CStr name, const Math::iv3& v3s) { GL::Uniform3i(GetUniformLocation(name), v3s.x, v3s.y, v3s.z); }
    void Shader::SetUniformIv4(CStr name, const Math::iv4& v4s) { GL::Uniform4i(GetUniformLocation(name), v4s.x, v4s.y, v4s.z, v4s.w); }
    void Shader::SetUniformIntArr(CStr name, Span<const int> xs)     { GL::Uniform1iv(GetUniformLocation(name), xs.Length(), xs.Data()); }
    void Shader::SetUniformIv2Arr(CStr name, Span<const Math::iv2> v2s) { GL::Uniform2iv(GetUniformLocation(name), v2s.Length(), (const int*)v2s.Data()); }
    void Shader::SetUniformIv3Arr(CStr name, Span<const Math::iv3> v3s) { GL::Uniform3iv(GetUniformLocation(name), v3s.Length(), (const int*)v3s.Data()); }
    void Shader::SetUniformIv4Arr(CStr name, Span<const Math::iv4> v4s) { GL::Uniform4iv(GetUniformLocation(name), v4s.Length(), (const int*)v4s.Data()); }
    void Shader::SetUniformUint(CStr name, uint x)                   { GL::Uniform1ui(GetUniformLocation(name), x); }
    void Shader::SetUniformUv2(CStr name, const Math::uv2& v2s) { GL::Uniform2ui(GetUniformLocation(name), v2s.x, v2s.y); }
    void Shader::SetUniformUv3(CStr name, const Math::uv3& v3s) { GL::Uniform3ui(GetUniformLocation(name), v3s.x, v3s.y, v3s.z); }
    void Shader::SetUniformUv4(CStr name, const Math::uv4& v4s) { GL::Uniform4ui(GetUniformLocation(name), v4s.x, v4s.y, v4s.z, v4s.w); }
    void Shader::SetUniformUintArr(CStr name, Span<const uint> xs)   { GL::Uniform1uiv(GetUniformLocation(name), xs.Length(), xs.Data()); }
    void Shader::SetUniformUv2Arr(CStr name, Span<const Math::uv2> v2s) { GL::Uniform2uiv(GetUniformLocation(name), v2s.Length(), (const uint*)v2s.Data()); }
    void Shader::SetUniformUv3Arr(CStr name, Span<const Math::uv3> v3s) { GL::Uniform3uiv(GetUniformLocation(name), v3s.Length(), (const uint*)v3s.Data()); }
    void Shader::SetUniformUv4Arr(CStr name, Span<const Math::uv4> v4s) { GL::Uniform4uiv(GetUniformLocation(name), v4s.Length(), (const uint*)v4s.Data()); }

    void Shader::SetUniformColor(CStr name, const Math::fColor3& color3) { GL::Uniform3f(GetUniformLocation(name), color3.r, color3.g, color3.b); }
    void Shader::SetUniformColor(CStr name, const Math::fColor&  color)  { GL::Uniform4f(GetUniformLocation(name), color.r, color.g, color.b, color.a); }
    void Shader::SetUniformTex(CStr name, const TextureBase& texture, TextureTarget target, int slot) {
        texture.Activate(target, slot);
        GL::Uniform1i(GetUniformLocation(name), slot);
    }
    
    void Shader::SetUniformMat2x2Arr(CStr name, Span<const Math::Matrix2x2> mats) { GL::UniformMatrix2fv  (GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat2x3Arr(CStr name, Span<const Math::Matrix2x3> mats) { GL::UniformMatrix2x3fv(GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat2x4Arr(CStr name, Span<const Math::Matrix2x4> mats) { GL::UniformMatrix2x4fv(GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat3x2Arr(CStr name, Span<const Math::Matrix3x2> mats) { GL::UniformMatrix3x2fv(GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat3x3Arr(CStr name, Span<const Math::Matrix3x3> mats) { GL::UniformMatrix3fv  (GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat3x4Arr(CStr name, Span<const Math::Matrix3x4> mats) { GL::UniformMatrix3x4fv(GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat4x2Arr(CStr name, Span<const Math::Matrix4x2> mats) { GL::UniformMatrix4x2fv(GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat4x3Arr(CStr name, Span<const Math::Matrix4x3> mats) { GL::UniformMatrix4x3fv(GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }
    void Shader::SetUniformMat4x4Arr(CStr name, Span<const Math::Matrix4x4> mats) { GL::UniformMatrix4fv  (GetUniformLocation(name), mats.Length(), false, (const float*)mats.Data()); }

    Tuple<Str, Str, Str> ShaderProgram::ParseShader(Str program) {
        Str sources[3];
        Str* current = nullptr;
        for (Str line : program.Lines()) {
            if (!line.StartsWith("// #shader")) continue;

            if (current) {
                current->TakeAfter(current->AsSpan().Unaddress(line.Data()));
            }

            line.Advance(11);
            if (line.StartsWith("vertex"))
                current = &sources[0];
            else if (line.StartsWith("fragment"))
                current = &sources[1];
            else if (line.StartsWith("geometry"))
                current = &sources[2];
            else current = nullptr;

            if (current) {
                *current = Str::Slice(line.DataEnd() + 1, program.DataEnd() - line.DataEnd() - 1);
            }
        };

        return { sources[0], sources[1], sources[2] };
    }

    ShaderProgram ShaderProgram::FromFile(CStr filepath) {
        ShaderProgram s {};
        const String file = Text::ReadFile(filepath).Assert();
        const auto [vtx, frg, geo] = ParseShader(file);
        s.rendererID = CreateShader(vtx, frg, geo);
        return s;
    }

    ShaderProgram ShaderProgram::FromFile(CStr vert, CStr frag, CStr geom) {
        ShaderProgram s {};
        s.rendererID = CreateShader(
            Text::ReadFile(vert).Assert(),
            Text::ReadFile(frag).Assert(),
            geom.IsEmpty() ? "" : Text::ReadFile(geom).Assert()
        );
        return s;
    }

    ShaderProgram ShaderProgram::FromFileCompute(CStr compute) {
        ShaderProgram s {};
        s.rendererID = CreateShaderCompute(
            Text::ReadFile(compute).Assert()
        );
        return s;
    }

    GraphicsID ShaderProgram::CompileShader(Str source, ShaderType::E type) {
        const GraphicsID id = GL::CreateShader((u32)type);
        const char* src = source.Data();
        const int length = (int)source.Length();
        GL::ShaderSource(id, 1, &src, &length);
        GL::CompileShader(id);

        int result;
        GL::GetShaderiv(id, GL::COMPILE_STATUS, &result);
    
        if (result == 0) {
            int len;
            GL::GetShaderiv(id, GL::INFO_LOG_LENGTH, &len);
            char* errbuf = Memory::QAlloca$(char, len);
            GL::GetShaderInfoLog(id, len, &len, errbuf);
            GLLogger().QError$("Compiling {} shader yielded compiler errors:\n{}", ShaderType::Name(type), errbuf);

            GL::DeleteShader(id);
            return 0;
        }

        return id;
    }

    GraphicsID ShaderProgram::CreateShader(Str vtx, Str frg, Str geo) {
        const GraphicsID program = GL::CreateProgram();
        const GraphicsID vs = CompileShaderVert(vtx);
        const GraphicsID fs = CompileShaderFrag(frg);
        const GraphicsID gm = geo.IsEmpty() ? 0 : CompileShaderGeom(geo);

        QGLCall$(GL::AttachShader(program, vs));
        QGLCall$(GL::AttachShader(program, fs));
        if (gm) QGLCall$(GL::AttachShader(program, gm));

        QGLCall$(GL::LinkProgram(program));
        QGLCall$(GL::ValidateProgram(program));
        
        QGLCall$(GL::DeleteShader(vs));
        QGLCall$(GL::DeleteShader(fs));
        if (gm) QGLCall$(GL::DeleteShader(fs));

        return program;
    }

    GraphicsID ShaderProgram::CreateShaderCompute(Str prog) {
        const GraphicsID program = GL::CreateProgram();
        const GraphicsID comp = CompileShaderCompute(prog);
        QGLCall$(GL::AttachShader(program, comp));
        QGLCall$(GL::LinkProgram(program));
        QGLCall$(GL::ValidateProgram(program));
        QGLCall$(GL::DeleteShader(comp));
        return program;
    }

    bool ShaderProgram::IsArrayUnif (ShaderUniformType type) { return (u32)type & 0x40; }
    bool ShaderProgram::IsMatrixUnif(ShaderUniformType type) { return (u32)type & 0x0C; }

    void ShaderProgram::ExecuteCompute(const Math::uv3& workSize) const {
        QGLCall$(GL::DispatchCompute(workSize.x, workSize.y, workSize.z));
    }

    void ShaderProgram::ExecuteCompute(u32 workX, u32 workY, u32 workZ) const {
        QGLCall$(GL::DispatchCompute(workX, workY, workZ));
    }

    ShaderParameter::ShaderParameter(Str name, const Math::fColor3& color3) : ShaderParameter(name, color3.AsRGBfVec()) {}
    ShaderParameter::ShaderParameter(Str name, const Math::fColor&  color)  : ShaderParameter(name, color.AsRGBAfVec()) {}
    ShaderParameter::ShaderParameter(Str name, Span<const Math::fColor3> color3s) : ShaderParameter(name, FV3_ARRAY, color3s.AsBytes()) {}
    ShaderParameter::ShaderParameter(Str name, Span<const Math::fColor>  colors)  : ShaderParameter(name, FV4_ARRAY, colors.AsBytes()) {}
    ShaderParameter::ShaderParameter(Str name, const TextureBase& tex, TextureTarget target, int slot) : ShaderParameter(name, slot) {
        tex.Activate(target, slot);
    }

    ShaderArgs::ShaderArgs(IList<ShaderParameter> p) {
        for (const auto& param : p) {
            Then(param);
        }
    }

    ShaderArgs& ShaderArgs::Then(const ShaderParameter& val) {
        rawBytes.Push((u8)val.utype);
        if (Shader::IsArrayUnif(val.utype) || Shader::IsMatrixUnif(val.utype)) {
            Bytes pay = val.payload.As<Bytes>();
            const usize len = pay.Length();
            const byte* dat = pay.Data();
            rawBytes.Extend(Bytes::BytesOf(len));
            rawBytes.Extend(Bytes::BytesOf(dat));
        } else {
            rawBytes.Extend(Bytes::BytesOf(val.payload.As<Array<u32, 4>>()));
        }
        rawBytes.Extend(val.name.AsBytes());
        rawBytes.Push('\0');
        return *this;
    }
}