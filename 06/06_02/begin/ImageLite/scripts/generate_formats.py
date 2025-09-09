formats = [
    {"name": "JPEG", "extension": ".jpg", "description": "Joint Photographic Experts Group"},
    {"name": "PNG", "extension": ".png", "description": "Portable Network Graphics"},
    {"name": "BMP", "extension": ".bmp", "description": "Bitmap Image File"}
]

with open('include/imagelite/formats.h', 'w') as f:
    f.write("// Auto-generated file - DO NOT EDIT\n")
    f.write("#pragma once\n\n")
    f.write("#include <string>\n")
    f.write("#include <array>\n\n")
    f.write("namespace imagelite {\n\n")
    
    f.write("struct ImageFormat {\n")
    f.write("    const char* name;\n")
    f.write("    const char* extension;\n")
    f.write("    const char* description;\n")
    f.write("};\n\n")
    
    f.write(f"constexpr size_t FORMAT_COUNT = {len(formats)};\n\n")
    
    f.write("constexpr ImageFormat SUPPORTED_FORMATS[] = {\n")
    for fmt in formats:
        f.write(f'    {{ "{fmt["name"]}", "{fmt["extension"]}", "{fmt["description"]}" }},\n')
    f.write("};\n\n")
    
    f.write("} // namespace imagelite\n")