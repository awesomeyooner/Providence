import cv2

# Open the camera (change the index if necessary)
cap = cv2.VideoCapture(0)

# List of common camera properties
property_ids = [
    cv2.CAP_PROP_BRIGHTNESS,
    cv2.CAP_PROP_CONTRAST,
    cv2.CAP_PROP_SATURATION,
    cv2.CAP_PROP_HUE,
    cv2.CAP_PROP_GAIN,
    cv2.CAP_PROP_EXPOSURE,
    cv2.CAP_PROP_FOURCC,
    cv2.CAP_PROP_FRAME_WIDTH,
    cv2.CAP_PROP_FRAME_HEIGHT,
    cv2.CAP_PROP_FPS,
    cv2.CAP_PROP_FORMAT,
    cv2.CAP_PROP_CHANNEL,
]

# Iterate through the properties and print their values
for prop_id in property_ids:
    value = cap.get(prop_id)
    print(f"{prop_id}: {value}")

# Release the camera
cap.release()