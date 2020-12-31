#define VERSION "1.0"

#include "jbig2enc/src/jbig2arith.cc"
#include "jbig2enc/src/jbig2comparator.cc"
#include "jbig2enc/src/jbig2sym.cc"
#include "jbig2enc/src/jbig2enc.cc"

#if defined(WIN32)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

struct Pix;
typedef struct Pix PIX;
extern "C" void pixDestroy(PIX **ppix);
extern "C" PIX *pixReadMem(const uint8_t *filedata, size_t filesize);
extern "C" PIX *pixRemoveColormap(PIX *pixs, int type);
extern "C" PIX *pixConvertTo1(PIX *pixs, int32_t threshold);

extern uint8_t *jbig2_encode_generic(struct Pix *const bw, const bool full_headers, const int xres, const int yres, const bool duplicate_line_removal, int *const length);

extern "C" DLLEXPORT uint8_t *jbig2Encode(void *data, size_t len, int *const out_len)
{
	PIX *pix = pixReadMem((const unsigned char *)data, len);
	if (!pix)
	{
		return NULL;
	}

	PIX *pix2 = pixConvertTo1(pix, 128);
	pixDestroy(&pix);
	pix = pix2;

	PIX *pixl = pixRemoveColormap(pix, 4);
	pixDestroy(&pix);

	if (!pixl)
	{
		return NULL;
	}

	uint8_t *ret = jbig2_encode_generic(pixl, false, 0, 0, true, out_len);
	pixDestroy(&pixl);
	return ret;
}
