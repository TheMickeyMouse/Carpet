#pragma once
#include "Utils/Math/Transform2D.h"
#include "Utils/Math/Transform3D.h"
#include "VertexBufferLayout.h"

#define Q_GL_DEFINE_VERTEX(T, DIM, MEMBS, ... /* may use 'custom transform' */) \
    static constexpr bool IS_GL_VERTEX = true; \
    using Self = T; \
    using Transformation = Quasi::Math::MatrixTransform##DIM; \
    static constexpr u32 DIMENSION = 0x##DIM >> 4; /* hacking ND into N */ \
    public: \
    inline static const auto VERTEX_LAYOUT = Quasi::Graphics::VertexBufferLayout::FromTypes< \
        Q_INVOKE(Q_ARGS_SKIP, Q_ITERATE_SEQUENCE(Q_GL_VERTLAYOUT_IT, MEMBS)) \
    >(); \
    \
    T Mul(const Math::MatrixTransform##DIM& _tr) const { \
        Q_IF_ARGS_ELSE((__VA_ARGS__), (return __VA_ARGS__(_tr);), ( \
            return T { Q_INVOKE(Q_ARGS_SKIP, Q_ITERATE_SEQUENCE(Q_GL_VERTTRANS_IT, MEMBS)) }; \
        ))\
    }

#define Q_GL_VERTTRANS_IT(MX) , .Q_ARGS_FIRST MX = Q_GL_VERTTRANS_WHEN_T MX
#define Q_GL_VERTTRANS_WHEN_T(M, ...) __VA_OPT__(Quasi::Graphics::Transform##__VA_ARGS__ Q_LPAREN() ) M __VA_OPT__(, _tr Q_RPAREN())
#define Q_GL_VERTLAYOUT_IT(X_) , decltype(Self:: Q_ARGS_FIRST X_)

#define QuasiDefineVertex$(...) Q_GL_DEFINE_VERTEX(__VA_ARGS__)

namespace Quasi::Graphics {
    template <class T> concept IVertex = requires { T::IS_GL_VERTEX; };

    template <class T>
    T TransformPosition(const T& p, const auto& transform) { return transform.Mul(p); }
    template <class T>
    T TransformNormal(const T& n, const auto& transform) { return transform.MulN(n); }
    template <class T> T&& TransfromCustom(T&& custom) { return (T&&)custom; }

    struct Vertex2D {
        Math::fv2 Position;

        QuasiDefineVertex$(Vertex2D, 2D, (Position, Position));
    };

    struct VertexColor2D {
        Math::fv2    Position;
        Math::fColor Color;

        QuasiDefineVertex$(VertexColor2D, 2D, (Position, Position)(Color));
    };

    struct VertexTexture2D {
        Math::fv2 Position;
        Math::fv2 TextureCoordinate;

        QuasiDefineVertex$(VertexTexture2D, 2D, (Position, Position)(TextureCoordinate));
    };

    struct Vertex3D {
        Math::fv3 Position;

        QuasiDefineVertex$(Vertex3D, 3D, (Position, Position));
    };

    struct VertexNormal3D {
        Math::fv3 Position;
        Math::fv3 Normal;

        QuasiDefineVertex$(VertexNormal3D, 3D, (Position, Position)(Normal, Normal));
    };

    struct VertexColor3D {
        Math::fv3    Position;
        Math::fColor Color;

        QuasiDefineVertex$(VertexColor3D, 3D, (Position, Position)(Color));
    };

    struct VertexColorTexture3D {
        Math::fv3    Position;
        Math::fColor Color;
        Math::fv2    TextureCoordinate;

        QuasiDefineVertex$(VertexColorTexture3D, 3D, (Position, Position)(Color)(TextureCoordinate));
    };

    struct VertexColorNormal3D {
        Math::fv3    Position;
        Math::fColor Color;
        Math::fv3    Normal;

        QuasiDefineVertex$(VertexColorNormal3D, 3D, (Position, Position)(Color)(Normal, Normal));
    };

    struct VertexTextureNormal3D {
        Math::fv3 Position;
        Math::fv2 TextureCoordinate;
        Math::fv3 Normal;

        QuasiDefineVertex$(VertexTextureNormal3D, 3D, (Position, Position)(TextureCoordinate)(Normal, Normal));
    };

    template <IVertex T>
    const VertexBufferLayout& VertexLayoutOf() { return T::VERTEX_LAYOUT; }
}