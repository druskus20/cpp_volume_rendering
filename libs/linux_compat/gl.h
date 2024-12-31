#pragma once

#ifdef _WIN32
#include <GL/wglew.h> // Windows-specific
#else
#include <EGL/egl.h> // Wayland-specific (EGL)
#include <GL/gl.h>
#endif

// Helper function to set the swap interval (V-Sync)
inline void setSwapInterval(int interval) {
#ifdef _WIN32
  if (wglSwapIntervalEXT) {
    wglSwapIntervalEXT(interval);
  }
#elif defined(__linux__)

  // Wayland-specific: Using EGL for Wayland
  EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (eglDisplay != EGL_NO_DISPLAY) {
    EGLint major, minor;
    if (eglInitialize(eglDisplay, &major, &minor)) {
      eglSwapInterval(eglDisplay, interval); // V-Sync via EGL
      eglTerminate(eglDisplay);              // Don't forget to terminate EGL
    }
  }
#endif
}

inline void initializeVSync() {
#ifdef _WIN32
  if (wglGetSwapIntervalEXT() > 0) {
    wglSwapIntervalEXT(1);
  }
#elif defined(__linux__)

  // Wayland-specific: Using EGL for Wayland
  EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (eglDisplay != EGL_NO_DISPLAY) {
    EGLint major, minor;
    if (eglInitialize(eglDisplay, &major, &minor)) {
      eglSwapInterval(eglDisplay, 1); // Enable V-Sync via EGL
      eglTerminate(eglDisplay);       // Don't forget to terminate EGL
    }
  }
#endif
}
