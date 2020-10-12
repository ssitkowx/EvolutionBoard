from pil import Image
import os

class BitmapConverter:
    def __init__ (v_this):
        print ('__init__')
        
        v_this.currentPath      = os.getcwd ()
        v_this.bitmapExtensions = ('.jpg', '.bmp', '.gif', '.png')
        v_this.imageExtension   = '.h'
        v_this.fileHead         = v_this.__getFileContent (v_this.currentPath + '\\Images\\Template\\head.h')
        v_this.fileTail         = v_this.__getFileContent (v_this.currentPath + '\\Images\\Template\\tail.h')
        
    def __getFileContent (v_this, v_filePath): 
        handle  = open (v_filePath, 'r')
        content = handle.read ()
        handle.close()  
        return content      

    def __getImageContent (v_this, v_bitmapPathWithName):
        handle  = Image.open (v_bitmapPathWithName).convert ('RGB')
        v_this.bitmapWidth, v_this.bitmapHeight = handle.size
        content = tuple (handle.getdata ())
        handle.close ()
        return content

    def __swapBytes (v_this, v_word):
        hByte = (v_word & 0xFF00) >> 8
        lByte = (v_word & 0x00FF)
        return ((lByte << 8) + hByte)
        
    def __converPixelToBigEndian (v_this, v_pixel):
        red          = (v_pixel [0] >> 3) & 0x1F
        green        = (v_pixel [1] >> 2) & 0x3F
        blue         = (v_pixel [2] >> 3) & 0x1F
        littleEndian = ((red << 11) + (green << 5) + blue)
        return v_this.__swapBytes (littleEndian)
            
    def __createImage (v_this, v_bitmapName, v_bitmapPathWithName, v_imagePathWithName):
        pixels      = v_this.__getImageContent (v_bitmapPathWithName)
        imageHandle = open (v_imagePathWithName, 'w')
        imageHandle.write (v_this.fileHead )
        imageHandle.write ('\n\nstatic const uint16_t ' + v_bitmapName + ' [] = \n{ \n    ')
        imageHandle.write ('0x{:04x}'.format (v_this.bitmapWidth) + ', ')
        imageHandle.write ('0x{:04x}'.format (v_this.bitmapHeight) + ', ')
        imageHandle.write ('\n    ')
            
        pixelNum = 1
        for pixel in pixels:
            bigEndian = v_this.__converPixelToBigEndian (pixel)
            imageHandle.write ('0x{:04x}'.format (bigEndian) + ', ')
            
            if pixelNum % 16 == 0:
                imageHandle.write ('\n    ')

            pixelNum = pixelNum + 1
            
        imageHandle.write ('\n};\n\n')
        imageHandle.write (v_this.fileTail)
        imageHandle.close ()
    
    def __searchFiles (v_this, v_path, v_extension): 
        filesList = []
        for root, dirs, files in os.walk (v_path): 
            for file in files:  
                if file.endswith (v_extension):
                    filesList.append (file)
        return filesList
                    
    def ConvertBitmapsToImages (v_this):
        print ('ConvertBitmapsToImages')

        for bitmapExtension in v_this.bitmapExtensions:
            bitmapsNameWithExtension = v_this.__searchFiles (v_this.currentPath + '\\Bitmaps', bitmapExtension)
            print ('Bitmaps founded: {0}'.format (bitmapsNameWithExtension))
    
            for bitmapNameWithExtension in bitmapsNameWithExtension:     
                bitmapPathWithName = v_this.currentPath + '\\Bitmaps\\' + bitmapNameWithExtension
                bitmapName         = bitmapNameWithExtension [:-4]
                imagePathWithName  = v_this.currentPath + '\\Images\\' + bitmapName + v_this.imageExtension
                
                print ('Convert {0} to {1}'.format (bitmapNameWithExtension, bitmapName + v_this.imageExtension))
                v_this.__createImage (bitmapName, bitmapPathWithName, imagePathWithName)
                    
def main ():
    bitmapConverter = BitmapConverter ()
    bitmapConverter.ConvertBitmapsToImages ()
        
if __name__ == "__main__": 
    main()