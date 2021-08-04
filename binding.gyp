{
  "conditions": [
    ['OS=="linux"', {
      "targets": [
        {
          "target_name": "js-ftrscan-api",
          "cflags!": [ "-fno-exceptions" ],
          "cflags_cc!": [ "-fno-exceptions" ],
          "sources": [
            "./src/index.cpp"
          ],
          "libraries": [
            "<(module_root_dir)/src/lib/libScanAPI.so"
          ],
          "include_dirs": [
            "<!@(node -p \"require('node-addon-api').include\")",
          ],
          "defines": [
            "NAPI_VERSION=<(napi_build_version)",
            "NAPI_DISABLE_CPP_EXCEPTIONS"
          ],
        }
      ]
    }],
    ['OS=="win"', {
      "targets": [
        {
          "target_name": "js-ftrscan-api",
          "cflags!": [ "-fno-exceptions" ],
          "cflags_cc!": [ "-fno-exceptions" ],
          "sources": [
            "./src/index.cpp"
          ],
          "libraries": [
            "<(module_root_dir)/src/lib/ftrScanAPI.lib"
          ],
          "include_dirs": [
            "<!@(node -p \"require('node-addon-api').include\")"
          ],
          "defines": [
            "NAPI_VERSION=<(napi_build_version)",
            "NAPI_DISABLE_CPP_EXCEPTIONS"
          ],
        }
      ]
    }],
  ]
}