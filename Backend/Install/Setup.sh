#! /usr/bin/env
echo Installing DL Libraries. Please wait..
echo Installing library
echo install pytorch
echo off
sudo apt update
# Install torch
pip install torch==1.12.1+cu113 torchvision==0.13.1+cu113 torchaudio==0.12.1 --extra-index-url https://download.pytorch.org/whl/cu113
python3 -m pip install -r requirements.txt
