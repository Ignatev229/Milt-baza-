echo off
cls
echo Installing DL Libraries. Please wait..
echo Installing library
echo install pytorch
pip install torch==1.12.1+cu113 torchvision==0.13.1+cu113 torchaudio==0.12.1 --extra-index-url https://download.pytorch.org/whl/cu113
pip install -r requirements.txt >nul 2>nul	
echo Finished install requirements.
pause


