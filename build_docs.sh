#!/bin/bash

python -m pip install -r docs/requirements.txt
make -C ./docs html
