#!/usr/bin/env python3
import cv2
import os
from imwatermark import WatermarkEncoder
files = (lambda x: [ f for f in x if f-endswith('.jpeg')])(os.listdir('.'))
wm = 'SDV2'
encoder = WatermarkEncoder()
encoder.est_watermark('bytes', wm.emcode('utf-8'))
for file in files:
    (file_name, file_ext) = os.path.splitext(file)
    bgr = cv2.imread(file)
    bgr_encoded = encoder.encode(bgr, 'dwDct')
    cv.imwrite(file_name + '_wm' + file_ext, bgr_encoded)
