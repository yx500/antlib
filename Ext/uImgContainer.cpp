//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl.h>
#include <map>
#include "uImgContainer.h"


#pragma resource "Ext\\ExtRc.res"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//typedef std::map<std::string,HENHMETAFILE , std::less<std::string> > imitems_type;
typedef std::map<std::string, TMetafile * , std::less<std::string> > imitems_type;



class t_imgcontainer : public imitems_type
{
public:
    t_imgcontainer() {};
    ~t_imgcontainer();
    TMetafile * findandaadd(const char * st_imagename);
};

t_imgcontainer::~t_imgcontainer()
{
    typedef imitems_type::value_type value_type;
    for (imitems_type::iterator p = begin(); p != end(); ++p) {
        TMetafile * emf = p->second;
        if (emf != NULL) delete emf;
    }
    clear();
}

TMetafile * LoadMetafileRes(const char* res, const char* type);
TMetafile * t_imgcontainer::findandaadd(const char * sz_imagename)
{
    TMetafile * emf = NULL;
    imitems_type::iterator p = find(sz_imagename);
    if (p == end()) {
        // добавлям!
        // смотрим в ресурсах

        int ii = atoi(sz_imagename);
        if (ii > 0) {
            if (FindResource(HInstance, MAKEINTRESOURCE(ii), "EMF"))
                emf = LoadMetafileRes(MAKEINTRESOURCE(ii), "EMF");
        }
        if (emf == NULL) {
            if (FindResource(HInstance, sz_imagename, "EMF"))
                emf = LoadMetafileRes(sz_imagename, "EMF");
        }

        if (emf == NULL) {
            String FN = String(imgcontainerpath.c_str()) + String(sz_imagename) + ".emf";
            if (FileExists(FN)) {
                //hemf =GetEnhMetaFile(FN.c_str());
                emf = new TMetafile();
                emf->LoadFromFile(FN);
            }
        }

        typedef imitems_type::value_type value_type;
        std::string st_imagename = sz_imagename;
        insert(value_type(st_imagename,   emf));
    } else {
        emf = p->second;
    }
    return emf;

}

t_imgcontainer imgcontainer;

std::string imgcontainerpath = ".\\Img\\";


TMetafile * LoadMetafileRes(const char* res, const char* type)
{
    int ResourceSize = SizeofResource(HInstance, FindResource(HInstance, res, type));
    // ...and get them into global memory.
    THandle* hResource = (unsigned int*) LoadResource(HInstance, FindResource(HInstance, res, type));
    // Keep 'um from moving around,...
    char *cResourcePtr = (char*)LockResource(hResource);
    if (cResourcePtr != NULL) {
        TMemoryStream * MS = new TMemoryStream();
        MS->Write(cResourcePtr, ResourceSize);
        MS->Seek(0, soFromBeginning);
        TMetafile * EMF = new TMetafile();
        EMF->LoadFromStream(MS);
        delete MS;
        return EMF;
    }
//  UnlockResource( hResource );
//  FreeResource( hResource );
    return NULL;
}




bool im_drawemf(void * vhdc,
                CONST RECT *lpRect,
                const char * szimagename,
                int animstep
               )
{
    HDC hdc=(HDC) vhdc;
    if (!szimagename) return false;
    std::string st_imagename = std::string(szimagename);
    if ( st_imagename.empty() ) return false;
    if (animstep > 0) {
        char anims[4];
        itoa(animstep, anims, 10);
        st_imagename = std::string(szimagename) + "_" + std::string(anims);
    }

    // ищем!
    TMetafile * emf = imgcontainer.findandaadd(st_imagename.c_str());
    // если не нашли с аним, то ищем без
    if (emf == NULL)
        emf = imgcontainer.findandaadd(szimagename);
    // рисуем
    if (emf != NULL) {
        if (PlayEnhMetaFile(
                    hdc,    // handle to a device context
                    (HENHMETAFILE)emf->Handle,   // handle to an enhanced metafile
                    lpRect  // pointer to bounding rectangle
                )) return true;

    }
    return false;
}



/*
Graphics::TBitmap * LoadBitmapRes(const char* res, const char* type)
{
  int ResourceSize = SizeofResource(HInstance,FindResource( HInstance,res,type ));
  // ...and get them into global memory.
  THandle* hResource =(unsigned int*) LoadResource( HInstance,FindResource( HInstance,res,type ));
  // Keep 'um from moving around,...
  char *cResourcePtr = (char*)LockResource(hResource);
  if (cResourcePtr!=NULL){
     TMemoryStream * MS=new TMemoryStream();
     MS->Write(cResourcePtr,ResourceSize);
     MS->Seek(0,soFromBeginning );
     Graphics::TBitmap * BMP= new Graphics::TBitmap();
     BMP->LoadFromStream(MS);
     delete MS;
     return BMP;
  }
//  UnlockResource( hResource );
//  FreeResource( hResource );
  return NULL;
}
*/

