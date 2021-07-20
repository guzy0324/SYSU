import random_forest as rf
import random_forest_gpu as rf_gpu

print('Numpy CPU:')
XY_list, threshold_list = rf.read('feature_dataset_256.csv', rf.NEG_REMAINDER_MUL_N)
print('PyTorch CPU:')
XY_list, threshold_list = rf_gpu.read('feature_dataset_256.csv', rf_gpu.NEG_REMAINDER_MUL_N)
print('PyTorch GPU:')
XY_list, threshold_list = rf_gpu.read('feature_dataset_256.csv', rf_gpu.NEG_REMAINDER_MUL_N, 'cuda:0')
