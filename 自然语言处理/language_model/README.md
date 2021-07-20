# language_model

## Requirements

|Name   |Version    |
|-------|-----------|
|python |3.7.6      |
|numpy  |1.18.4     |
|torch  |1.4.0      |
|tqdm   |4.46.0     |
|matplot|3.2.1      |

## Data set

[msrseg.rar](https://github.com/guzy0324/BiLSTM_CRF/releases/download/v0.1.0/msrseg.rar)
[65](https://github.com/guzy0324/language_model/releases/download/0.0.0/65)
[resegmenting_result.utf8](https://github.com/guzy0324/language_model/releases/download/0.0.0/resegmenting_result.utf8)

## How to run my codes

You may need to change the `SUFFIX` in language_model.py ahead of running.

```python
SEED = 1
START_TAG, END_TAG = "<s>", "<e>"
GPU = True
LR = 0.005
MAX_EPOCH = 128
BATCH_SIZE = 16
EMBEDDING_DIM = 128
HIDDEN_DIM = 128
SHUFFLE = True
SET_SIZE = 100000
TRAINED_EPOCH = -1
SUFFIX = '_100000_128_128_0.005'
```

1. Resegmenting

    ```shell
    python resegmentation.py
    ```

2. Training

    ```shell
    python language_model.py
    ```

3. Calculating the loss

    ```shell
    python language_model_loss.py
    ```

4. Testing

    ```shell
    python language_model_test.py
    ```

5. Drawing figures

    ```shell
    python draw3000.py
    ```

    ```shell
    python draw100000.py
    ```

    ```shell
    python draw100000 (2).py
    ```

    ```shell
    python draw100000 (3).py
    ```

## Pre-trained models

|SET_SIZE|LR    |MAX_EPOCH|EMBEDDING_DIM|HIDDEN_DIM|Link|
|--------|------|---------|-------------|----------|----|
|3000    |0.01  |128      |128          |16        |[model_3000_128_128_0.01.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_3000_128_128_0.01.7z)|
|100000  |0.0005|128      |128          |16        |[model_100000_128_128_0.005_0-15.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_0-15.7z), [model_100000_128_128_0.005_16-31.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_16-31.7z), [model_100000_128_128_0.005_32-47.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_32-47.7z), [model_100000_128_128_0.005_48-63.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_48-63.7z), [model_100000_128_128_0.005_64-79.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_64-79.7z), [model_100000_128_128_0.005_80-95.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_80-95.7z), [model_100000_128_128_0.005_96-111.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_96-111.7z), [model_100000_128_128_0.005_112-127.7z](https://github.com/guzy0324/language_model/releases/download/0.0.0/model_100000_128_128_0.005_112-127.7z)|
