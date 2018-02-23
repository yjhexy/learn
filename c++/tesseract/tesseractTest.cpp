#include <string>
using std::string;//新增

#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
  
int main(int argc, char* argv[])  
{  
    const char * image = "image.jpg";  
    const char * outputbase = "out";  
      
    tesseract::TessBaseAPI api;  
    api.SetOutputName(outputbase);  
  
    int rc = api.Init(NULL, "eng", tesseract::OEM_DEFAULT);  
    if (rc) {  
        printf("Could not initialize tesseract.\n");  
        exit(1);  
    }  
  
    //api.SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");  
  
    Pix* pixs = pixRead(image);  
    if (!pixs) {  
        printf("Cannot open input file: %s\n", image);  
        exit(2);  
    }  
    api.SetImage(pixs);  
  
    tesseract::TessResultRenderer* renderer = new tesseract::TessTextRenderer(outputbase);  
    if (!api.ProcessPages(image, NULL, 0, renderer)) {  
        printf("Error during processing.\n");  
    }  
  
    delete renderer;  
    pixDestroy(&pixs);  
    return 0;  
}   