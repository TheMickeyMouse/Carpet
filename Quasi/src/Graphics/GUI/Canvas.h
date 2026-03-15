#pragma once
#include "Interactable.h"
#include "Mesh.h"
#include "UIVertex.h"
#include "RenderObject.h"
#include "TextureAtlas.h"
#include "Fonts/TextAlign.h"

namespace Quasi::Graphics {
    class Font;

    struct DrawAttributes {
        Math::fColor fillColor = 1;
        Math::fColor strokeColor = 0;
        float strokeWeight = 5;
        u32 drawStyle = 0;
        OptRef<const Font> currentFont = nullptr;
    };

    struct Gradient {
        Math::fv2    startPoint, direction;
        Math::fColor startColor, endColor;

        static Gradient Vertical(float s, float e, const Math::fColor& sc, const Math::fColor& ec);
        static Gradient Horizontal(float s, float e, const Math::fColor& sc, const Math::fColor& ec);

        Math::fColor At(const Math::fv2& p) const;
    };

    class UIMesh : public Mesh<UIVertex> {
    public:
        void SetTextureFill();
        void FillGradient(const Gradient& g);
        void OverlayGradient(const Gradient& g);
    };

    namespace UIDetails {
        struct SpriteOptions {
            Math::fColor tint = 1;
            Math::fRect2D mask = { 0, 1 };
        };
    }

    class Canvas {
        RenderObject<UIVertex> renderCanvas;
        UIMesh worldMesh;
        OptRef<UIMesh> drawMesh = nullptr; // can be set to any mesh. by default it draws to the world mesh
        DrawAttributes drawAttr;
        // TODO: replace this with a better method to fetch fonts
        Font defaultFont = Font::LoadFile(R"(C:\Windows\Fonts\arial.ttf)", 64);

        Vec<Ref<Interactable>> interactables;

        static constexpr u32 MAX_TEXTURE_SAMPLERS = 8;
        GraphicsID textures[MAX_TEXTURE_SAMPLERS] = {};
        u32 usedTextures = 0;
    public:
        Math::Transform2D transform;

        Canvas();
        Canvas(GraphicsDevice& gd);

        enum ArcMode {
            OPEN, CHORD, CLOSED
        };
        enum ArcDirection {
            CCW, CW, MAJOR, MINOR
        };

        void DrawTriangle(const Math::fv2& p1, const Math::fv2& p2, const Math::fv2& p3);
        void DrawQuad(const Math::fv2& p1, const Math::fv2& p2, const Math::fv2& p3, const Math::fv2& p4);
        void DrawSquare(const Math::fv2& position, float size, bool center = true);
        void DrawRect(const Math::fRect2D& rect);
        void DrawRoundedSquare(const Math::fv2& position, float size, float radius, bool center = true);
        void DrawVarRoundedSquare(const Math::fv2& position, float size, float tr, float br, float tl, float bl, bool center = true);
        void DrawRoundedRect(const Math::fRect2D& rect, float radius);
        void DrawVarRoundedRect(const Math::fRect2D& rect, float tr, float br, float tl, float bl);
        void DrawCircle(const Math::fv2& position, float radius, bool center = true);
        void DrawEllipse(const Math::fRect2D& bounds);
        void DrawEllipse(const Math::fv2& position, const Math::fv2& axis1, const Math::fv2& axis2);
        void DrawArc(const Math::fv2& center, float radius, const Math::Rotor2D& startAngle, const Math::Rotor2D& endAngle, ArcDirection direction = CCW, ArcMode mode = OPEN);
        void DrawArcCCW(const Math::fv2& center, float radius, const Math::Rotor2D& startAngle, const Math::Rotor2D& endAngle, ArcMode mode = OPEN);
        // void DrawEllArc(const Math::fv2& center, const Math::fv2& size, float startAngle, float stopAngle, ArcMode mode = OPEN);
        void DrawPoint(const Math::fv2& position);
        void DrawLine(const Math::fv2& start, const Math::fv2& end);

        void DrawMesh(const UIMesh& mesh);

        using SpriteOptions = UIDetails::SpriteOptions;

        void DrawTexture (const Texture2D& texture, const Math::fv2& pos, const Math::fv2& size, bool center = true, const SpriteOptions& options = {});
        void DrawTextureW(const Texture2D& texture, const Math::fv2& pos, float w, bool center = true, const SpriteOptions& options = {});
        void DrawTextureH(const Texture2D& texture, const Math::fv2& pos, float h, bool center = true, const SpriteOptions& options = {});
        // full method
        void DrawTextureEx(const Texture2D& texture, const Math::fRect2D& rect, const SpriteOptions& options = {});

        void DrawSTexture  (const SubTexture& subtex, const Math::fv2& pos, const Math::fv2& size, bool center = true, const Math::fColor& tint = 1);
        void DrawSTextureW (const SubTexture& subtex, const Math::fv2& pos, float w, bool center = true, const Math::fColor& tint = 1);
        void DrawSTextureH (const SubTexture& subtex, const Math::fv2& pos, float h, bool center = true, const Math::fColor& tint = 1);
        void DrawSTextureEx(const SubTexture& subtex, const Math::fRect2D& rect, const Math::fColor& tint = 1);

        void DrawText(Str text, float fontSize, const Math::fv2& pos, const TextAlign& align = {});

        void ShowHitboxes();

        // if for some reason we either:
        //      1. run out of index/vertex memory
        //   or 2. use up all the texture slots,
        // we draw the batch immediately to clear the current mesh,
        // leaving up more space for more objects
        void ForceDrawCurrentBatch();

        UIMesh& DestinationMesh();
        struct Batch : UIMesh::Batch {
            Canvas& canvas;
            UIVertex storedPoint;

            void SetColor(const Math::fColor& color);
            void SetFill();
            void SetStroke();
            void SetPrim(u32 prim);
            void SetPrimAndStyle(u32 primAndStyle);
            void SetPosition(const Math::fv2& point);
            void SetUV(float u, float v);
            void SetSTUV(float s, float t, float u, float v = 0);
            void SetTextureCoord(float u, float v);
            void SetTexture(GraphicsID textureID);
            void SetSDF(GraphicsID sdf);
            u32  RegTexture(GraphicsID textureID);
            void SetNoTexture();
            void Point(const Math::fv2& position);
            void PointCirc(const Math::fv2& position, float u, float v);
            void PointArc(const Math::fv2& position, float u, float v, float radiusRatio);
            void PointQBezGeneric(const Math::fv2& position, float u, float v, bool flip); // start
            void PointQBezA(const Math::fv2& position, bool flip); // start
            void PointQBezB(const Math::fv2& position, bool flip); // control
            void PointQBezC(const Math::fv2& position, bool flip); // end
            void PointQTriple(const Math::fv2& position, bool innerSide); // flat + start + end
            void PointQDoubleS(const Math::fv2& position, bool innerSide); // flat + start
            void PointQDoubleE(const Math::fv2& position, bool innerSide); // flat + end
            void PointQDoubleC(const Math::fv2& position, bool innerSide); // flat + control
            void PointsQBez(Span<const Math::fv2> bezpoints, bool innerSide);
            void PointsQBezClosed(Span<const Math::fv2> outer, Span<const Math::fv2> inner);
            void Push();
            void Push(const Math::fv2& point);
            void PushAsPlain();

            // returns advance
            float PushGlyph(const Glyph& glyph, float scaling, const Math::fv2& position, const Texture2D& atlas);
        };
        Batch NewBatch();

    private:
        bool NeedDrawFill()   const { return !(drawAttr.drawStyle & UIRender::NO_FILL); }
        bool NeedDrawStroke() const { return !(drawAttr.drawStyle & UIRender::NO_STROKE); }

        void DrawSimpleLine(const Math::fv2& start, const Math::fv2& end, const Math::fv2& tangent);
        void DrawLineCap(const Math::fv2& point, const Math::fv2& tangent);
        void DrawLineJoin(const Math::fv2& point, const Math::fv2& tangent1, const Math::fv2& tangent2);

        // draws a semicircle (pi) -> none (0)
        // forward is the middle of the section (scaled with radius)
        // cos is half of the angle of the full section, so is sin
        void DrawHalfCircularChord(const Math::fv2& center, const Math::fv2& forward, float cos, float sin, const Math::fColor& color);
        void DrawHalfCircle(const Math::fv2& center, const Math::fv2& forward, const Math::fColor& color);
        void DrawSimpleCircle(const Math::fv2& center, float radius, const Math::fColor& color);
        void DrawQuarterChord(const Math::fv2& center, const Math::fv2& rightMostSide, const Math::fColor& color);
        void DrawSimpleEllipse(const Math::fv2& center, const Math::fv2& radii, const Math::fColor& color);
        void DrawSimpleEllipse(const Math::fRect2D& bounds, const Math::fColor& color);
        void DrawCircleOutline(const Math::fv2& center, float radius, float thickness, const Math::fColor& color);

        // by default the arc is on the first quadrant, which can be changed by start
        void DrawQuarterArc(const Math::fv2& center, const Math::Rotor2D& start, float radius, float thickness, const Math::fColor& color);
        void DrawCircularArcCCW(const Math::fv2& center, const Math::Rotor2D& mid, Math::Rotor2D step, float radius, float thickness, const Math::fColor& color);

        void DrawSimpleRect(const Math::fRect2D& rect, const Math::fColor& color);
        void DrawSimpleRoundedRect(const Math::fRect2D& outer, float radius, const Math::fColor& color);
        void DrawSimpleVarRoundRect(const Math::fRect2D& outer, float tr, float br, float tl, float bl, const Math::fColor& color);
        void DrawRectStroke(const Math::fRect2D& rect);

        void DrawTextLine(Str line, float relSize, const Math::fv2& pos, float letterSpacing, const Font& font);
        void DrawTextJustify(Str line, float relSize, const Math::fv2& pos, float letterSpacing, float width, const Font& font);
    public:

        enum CurveMode {
            OPEN_CURVE, CLOSED_CURVE
        };
        struct Path {
            Canvas& canvas;
            u32 closing = OPEN_CURVE;
            enum {
                OPEN_CURVE_SECOND_POINT = 2,
                OPEN_CURVE_MIDDLE_POINT = 3,
                CLOSED_CURVE_SECOND_POINT = 4,
                CLOSED_CURVE_MIDDLE_POINT = 5,
                COMPLETED = -1,
            };
        private:
            Math::fv2 firstPoint, firstTangent, lastPoint, lastTangent;

            bool NoPointsYet();
            void BeginLineSegment(const Math::fv2& p);
            void EndLineSegment(const Math::fv2& p, const Math::fv2& tangent);

            void DrawCircularArcCCW(const Math::fv2& startPoint, const Math::fv2& center, const Math::Rotor2D& turn);
        public:
            Path(Canvas& canvas, CurveMode mode) : canvas(canvas), closing(mode) {}
            void AddPoint(const Math::fv2& point);
            // from lastPoint to current point is a full turn
            void AddCircularArc(const Math::fv2& center, const Math::Rotor2D& turn, ArcDirection dir = CCW);
            void AddQuadBez(const Math::fv2& control, const Math::fv2& end);
            void ClosePath();
            ~Path();
        };
        Path NewPath(CurveMode mode = CLOSED_CURVE);

        DrawAttributes& DrawAttr() { return drawAttr; }
        const DrawAttributes& DrawAttr() const { return drawAttr; }

        const Font& GetCurrentFont() const;

        void StrokeWeight(float weight);
        void StrokeCap(UIRender::RenderStyle cap);
        void StrokeJoin(UIRender::RenderStyle join);

        void Fill(const Math::fColor& fillColor);
        void Stroke(const Math::fColor& strokeColor);
        void NoStroke();
        void NoFill();

        struct DeferRenderScope {
            Canvas& canvas;
            OptRef<UIMesh> prevDestination;
            DeferRenderScope(Canvas& canvas, UIMesh& newDest);
            ~DeferRenderScope();
        };
        DeferRenderScope RenderTo(UIMesh& mesh);

        struct PushStylesScope {
            Canvas& canvas;
            DrawAttributes originalAttr;
            PushStylesScope(Canvas& canvas);
            ~PushStylesScope();
        };
        PushStylesScope PushStyles();

        Math::fv2 TransformToWorldSpace(const Math::fv2& point) const;
        void SetViewport(const Math::fRect2D& viewport);

        void Update(float dt);
        void AddInteractable(Ref<Interactable> inter);
        void RemoveInteractable(Ref<Interactable> inter);

        void BeginFrame();
        void EndFrame();
    };
}
