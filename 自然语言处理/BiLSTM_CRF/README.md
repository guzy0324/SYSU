# BiLSTM_CRF
## Requirements

|Name   |Version    |
|-------|-----------|
|python |3.8.3      |
|numpy  |1.18.5     |
|torch  |1.7.0+cu110|
|tqdm   |4.47.0     |
|matplot|3.2.2      |

## Data set
[msrseg.rar](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.1.0/msrseg.rar)

## How to run my codes
1. Training

    ```shell
    python bilstm_crf.py
    ```

2. Testing with `msr_test_gold.utf8`

    ```shell
    python bilstm_crf_test_gold.py
    ```

3. Testing with `msr_test.utf8`

    ```shell
    python bilstm_crf_test.py
    ```

4. Drawing the Average F1-Epoch figure
    ```shell
    python draw.py
    ```

## Pre-trained models and their average F1 score
|MAX_EPOCH|BATCH_SIZE|EMBEDDING_DIM|HIDDEN_DIM|Link                                                                      |
|---------|----------|-------------|----------|--------------------------------------------------------------------------|
|1        |128       |16           |16        |[1.128.16.16.7z](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.0.0/1.128.16.16.7z)   |
|1        |128       |128          |16        |[1.128.128.16.7z](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.0.0/1.128.128.16.7z)  |
|1        |128       |128          |128       |[1.128.128.128.7z](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.0.0/1.128.128.128.7z) |
|1        |256       |128          |128       |[1.256.128.128.7z](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.0.0/1.256.128.128.7z) |
|68       |128       |128          |128       |[68.128.128.128.7z](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.0.0/68.128.128.128.7z)|