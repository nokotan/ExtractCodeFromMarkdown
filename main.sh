#!/bin/bash

if [ ! -e "Zenn.Public" ]; then
    git clone https://github.com/Reputeless/Zenn.Public
fi

python3 main.py Generated Zenn.Public/books/siv3d-documentation/*.md
