// Direct3D 環境では HLSL を、
// OpenGL 環境では GLSL を、
// Web 環境では GLSL ES を読み込んでピクセルシェーダを作成
PixelShader ps = HLSL{ ... } | GLSL{ ... } | ESSL{ ... };
