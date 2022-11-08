#!/bin/bash

if [ ! -e "Zenn.Public" ]; then
    git clone https://github.com/Reputeless/Zenn.Public
fi

if [ ! -e "siv3d.docs" ]; then
    git clone https://github.com/Siv3D/siv3d.docs
fi

python3 main.py ZennBook Zenn.Public/books/siv3d-documentation/*.md
python3 main.py Siv3DDocs siv3d.docs/docs/ja-jp/*/*.md
