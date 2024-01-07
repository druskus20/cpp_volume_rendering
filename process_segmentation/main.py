import slicerio
import json
import nrrd

input_filename = "../data/Segmented/Segmentation_1.seg.nrrd"
output_filename = "../data/Segmented/Segmentation_1_out.seg.nrrd"
segment_names_to_labels = [("Lobster", 1), ("Cup", 2), ("Ground", 3)]

segmentation_info = slicerio.read_segmentation_info(input_filename)

segment0 = slicerio.segment_from_name(segmentation_info, "Lobster")
print("First segment info:\n" + json.dumps(segment0, sort_keys=False, indent=4))

voxels, header = nrrd.read(input_filename)
print(header)
print(voxels)
print(voxels.shape)

segment_names = slicerio.segment_names(segmentation_info)

print("segment_names: ", segment_names)


extracted_voxels, extracted_header = slicerio.extract_segments(voxels, header, segmentation_info, segment_names_to_labels)

found = [0.0] * 4
# iterate through every single point
for i in range(0, extracted_voxels.shape[0]):
    for j in range(0, extracted_voxels.shape[1]):
        for k in range(0, extracted_voxels.shape[2]):
            found[int(extracted_voxels[i][j][k])] += 1.0

print(found)
total = found[1] + found[2] + found[3]
total_voxels = found[0] + found[1] + found[2] + found[3]
print("total: ", total)
print("total voxels: ", total_voxels)
print("theoretical total voxels: ", 256 * 256 * 178)
print("fragment of segmented voxels: ", total / total_voxels)

# Write only the voxels to a file

import numpy as np

# Assuming you have a NumPy array named 'data_array'
data_array = np.array(extracted_voxels)
data_array = np.random.randint(4, size=(256, 256, 178), dtype=np.uint8)


# convert to array of bytes, since our numbers are small enough


# Specify the file path and name
file_path = output_filename

# Write the array to a binary file
data_array.tofile(file_path)

