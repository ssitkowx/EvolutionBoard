# BitmapConverter

# I. Description:
Script is used to convert bitmaps to images. Script works with such file formats as jpg, bmp, gif, and png.

# II. Assumptions:
The code stored in BitmapConverter.py is adapted to ILI9341 settings in EvolutionBoard project:
- sixteen bits pixels in big endian format,
- format of the converted .h files.

# III. Structure:
- BitmapConverter
  - Bitmaps
  - Images
    - Templates
      - head.h
	  - tail.h
  - BitmapConverter.py

# IV. Configuration:
- Python 3.8.3 version,
- Python pil library.

# V. Script execution:
Before executing the script, you should:
- have the file structure as in point III,
- be in the same folder with the BitmapConverter.py script

for example:
1. Open windows command interpreter,
2. type cd C:\Users\sitko\Desktop\Projekty\GIT\EvolutionBoard\Project\Logic\Resources\BitmapConverter,
3. execute C:\Users\sitko\AppData\Local\Programs\Python\Python38-32\python.exe C:\Users\sitko\Desktop\Projekty\GIT\EvolutionBoard\Project\Logic\Resources\BitmapConverter.py,
4. go to the image location to check the generated files. 

The script also displays the found bitmaps and the converted files.



