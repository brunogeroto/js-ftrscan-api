{
  "targets": [
    {
      "target_name": "js-ftrscan-api",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
      ],
      "defines": [
        "NAPI_VERSION=<(napi_build_version)",
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ],
      'conditions': [
        ['OS=="linux"', {
          "libraries": [
            "<(module_root_dir)/src/lib/libScanAPI.so"
          ],
        }],
        ['OS=="win"', {
          'libraries': [
            'ftrScanAPI.lib',
          ], 
          'link_settings': {
            'library_dirs': [
              'src/lib',
            ]
          },
          'copies':[
            { 
              'destination': './build/Release',
              'files':[
                './src/lib/ftrScanAPI.dll'
              ]
            }
          ]
        }],
      ]
    }
  ]
}