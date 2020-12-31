package jbig2enc

import (
	"fmt"
	"unsafe"
)

//#cgo LDFLAGS: -lpng -llept
//#include <stdlib.h>
//
//typedef unsigned char uint8_t;
//extern uint8_t *jbig2Encode(void *data, size_t len, int *const out_len);
import "C"

func Encode(bs []byte) ([]byte, error) {
	var datalen C.int
	data := C.jbig2Encode(unsafe.Pointer(&bs[0]), C.size_t(len(bs)), &datalen)
	if data == nil {
		return nil, fmt.Errorf("failed to encode")
	}
	defer C.free(unsafe.Pointer(data))

	out := C.GoBytes(unsafe.Pointer(data), datalen)
	return out, nil
}
