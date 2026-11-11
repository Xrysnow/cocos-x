#!/usr/bin/env python3
"""Convert the supplied cocos icon to platform sizes without redrawing it."""

import json
from pathlib import Path

from PIL import Image


ROOT = Path(__file__).resolve().parents[1]


def save_png(image, path, size):
    path.parent.mkdir(parents=True, exist_ok=True)
    image.resize((size, size), Image.Resampling.LANCZOS).save(path)


def save_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


def main():
    with Image.open(ROOT / "icons/cocos4_1024.png") as source:
        image = source.convert("RGBA")
    save_png(image, ROOT / "Resources/icon.png", 256)
    windows = ROOT / "proj.win32/res/game.ico"
    windows.parent.mkdir(parents=True, exist_ok=True)
    image.save(windows, sizes=[(size, size) for size in (16, 24, 32, 48, 64, 128, 256)])
    image.save(ROOT / "proj.ios_mac/mac/Icon.icns")

    for density, size in (("mdpi", 48), ("hdpi", 72), ("xhdpi", 96),
                          ("xxhdpi", 144), ("xxxhdpi", 192)):
        save_png(image, ROOT / f"proj.android/app/res/mipmap-{density}/ic_launcher.png", size)

    # App Store assets must not contain an alpha channel.
    opaque = Image.new("RGB", image.size, "white")
    opaque.paste(image, mask=image.getchannel("A"))
    catalog = ROOT / "proj.ios_mac/ios/Images.xcassets"
    metadata = {"version": 1, "author": "xcode"}
    save_json(catalog / "Contents.json", {"info": metadata})
    icons = []
    for idiom, sizes, scales in (("iphone", (20, 29, 40, 60), (2, 3)),
                                  ("ipad", (20, 29, 40, 76), (1, 2)),
                                  ("ipad", (83.5,), (2,)),
                                  ("ios-marketing", (1024,), (1,))):
        for size in sizes:
            for scale in scales:
                name = f"Icon-{size}@{scale}x.png"
                save_png(opaque, catalog / "AppIcon.appiconset" / name, round(size * scale))
                icons.append({"idiom": idiom, "size": f"{size}x{size}",
                              "scale": f"{scale}x", "filename": name})
    save_json(catalog / "AppIcon.appiconset/Contents.json", {"images": icons, "info": metadata})


if __name__ == "__main__":
    main()
