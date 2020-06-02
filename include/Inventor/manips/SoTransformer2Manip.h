#ifndef COIN_SOTRANSFORMER2MANIP_H
#define COIN_SOTRANSFORMER2MANIP_H

#include <Inventor/manips/SoTransformManip.h>


class COIN_DLL_API SoTransformer2Manip : public SoTransformManip
{
    typedef SoTransformManip inherited;

    SO_NODE_HEADER(SoTransformer2Manip);

  public:

    static void initClass(void);
    SoTransformer2Manip(void);

    SbBool isLocateHighlighting(void);
    void setLocateHighlighting(SbBool onoff);

    void unsquishKnobs(void);

  protected:

    ~SoTransformer2Manip();
};

#endif /* COIN_SOTRANSFORMER2MANIP_H */
