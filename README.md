# Entpy - entropy, information and complexity calculations

Some calculations I find interesting and wanted a collection of.

## Usage

Probably, for now, install for development:

    $ pipenv sync
    $ git submodule update --init --recursive
    $ python setup.py develop

## More to follow

```python
>>> import numpy as np
>>> import entpy.gen
>>> print(np.array2string(entpy.gen.sierpinski(32), separator='', threshold=10000, max_line_width=1000, formatter={'int':lambda x:' ^'[x]}))
[[                                ^                                ]
 [                               ^ ^                               ]
 [                              ^   ^                              ]
 [                             ^ ^ ^ ^                             ]
 [                            ^       ^                            ]
 [                           ^ ^     ^ ^                           ]
 [                          ^   ^   ^   ^                          ]
 [                         ^ ^ ^ ^ ^ ^ ^ ^                         ]
 [                        ^               ^                        ]
 [                       ^ ^             ^ ^                       ]
 [                      ^   ^           ^   ^                      ]
 [                     ^ ^ ^ ^         ^ ^ ^ ^                     ]
 [                    ^       ^       ^       ^                    ]
 [                   ^ ^     ^ ^     ^ ^     ^ ^                   ]
 [                  ^   ^   ^   ^   ^   ^   ^   ^                  ]
 [                 ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^                 ]
 [                ^                               ^                ]
 [               ^ ^                             ^ ^               ]
 [              ^   ^                           ^   ^              ]
 [             ^ ^ ^ ^                         ^ ^ ^ ^             ]
 [            ^       ^                       ^       ^            ]
 [           ^ ^     ^ ^                     ^ ^     ^ ^           ]
 [          ^   ^   ^   ^                   ^   ^   ^   ^          ]
 [         ^ ^ ^ ^ ^ ^ ^ ^                 ^ ^ ^ ^ ^ ^ ^ ^         ]
 [        ^               ^               ^               ^        ]
 [       ^ ^             ^ ^             ^ ^             ^ ^       ]
 [      ^   ^           ^   ^           ^   ^           ^   ^      ]
 [     ^ ^ ^ ^         ^ ^ ^ ^         ^ ^ ^ ^         ^ ^ ^ ^     ]
 [    ^       ^       ^       ^       ^       ^       ^       ^    ]
 [   ^ ^     ^ ^     ^ ^     ^ ^     ^ ^     ^ ^     ^ ^     ^ ^   ]
 [  ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^   ^  ]
 [ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ]]
```

## License

GNU GPLv3
