#pragma once

#include<memory>

template<class T>
void SafeReleasePointer(T** ppT) {
	// Release raw pointers
	if (*ppT) {
		delete (*ppT);
		*ppT = NULL;
	}
}

template<class T>
void SafeReleaseCom(T** ppT) {
	// Release COM interface pointers
    if (*ppT) {
		(*ppT)->Release();
        *ppT = NULL;
    }
}