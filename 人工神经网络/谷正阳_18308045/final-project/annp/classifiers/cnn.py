from builtins import object
import numpy as np

from ..layers import *
from ..fast_layers import *
from ..layer_utils import *


class ThreeLayerConvNet(object):
    """
    A three-layer convolutional network with the following architecture:

    conv - relu - 2x2 max pool - affine - relu - affine - softmax

    The network operates on minibatches of data that have shape (N, C, H, W)
    consisting of N images, each with height H and width W and with C input
    channels.
    """

    def __init__(
        self,
        input_dim=(3, 32, 32),
        num_filters=32,
        filter_size=7,
        hidden_dim=100,
        num_classes=10,
        weight_scale=1e-3,
        reg=0.0,
        dtype=np.float32,
    ):
        """
        Initialize a new network.

        Inputs:
        - input_dim: Tuple (C, H, W) giving size of input data
        - num_filters: Number of filters to use in the convolutional layer
        - filter_size: Width/height of filters to use in the convolutional layer
        - hidden_dim: Number of units to use in the fully-connected hidden layer
        - num_classes: Number of scores to produce from the final affine layer.
        - weight_scale: Scalar giving standard deviation for random initialization
          of weights.
        - reg: Scalar giving L2 regularization strength
        - dtype: numpy datatype to use for computation.
        """
        self.params = {}
        self.reg = reg
        self.dtype = dtype

        ############################################################################
        # TODO: Initialize weights and biases for the three-layer convolutional    #
        # network. Weights should be initialized from a Gaussian centered at 0.0   #
        # with standard deviation equal to weight_scale; biases should be          #
        # initialized to zero. All weights and biases should be stored in the      #
        #  dictionary self.params. Store weights and biases for the convolutional  #
        # layer using the keys 'W1' and 'b1'; use keys 'W2' and 'b2' for the       #
        # weights and biases of the hidden affine layer, and keys 'W3' and 'b3'    #
        # for the weights and biases of the output affine layer.                   #
        #                                                                          #
        # IMPORTANT: For this assignment, you can assume that the padding          #
        # and stride of the first convolutional layer are chosen so that           #
        # **the width and height of the input are preserved**. Take a look at      #
        # the start of the loss() function to see how that happens.                #
        ############################################################################
        # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

        self.params['W1'] = weight_scale * np.random.randn(num_filters, input_dim[0], filter_size, filter_size)
        self.params['b1'] = np.zeros(num_filters)
        self.params['W2'] = weight_scale * np.random.randn(num_filters * input_dim[1] // 2 * input_dim[2] // 2, hidden_dim)
        self.params['b2'] = np.zeros(hidden_dim)
        self.params['W3'] = weight_scale * np.random.randn(hidden_dim, num_classes)
        self.params['b3'] = np.zeros(num_classes)

        # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
        ############################################################################
        #                             END OF YOUR CODE                             #
        ############################################################################

        for k, v in self.params.items():
            self.params[k] = v.astype(dtype)

    def loss(self, X, y=None):
        """
        Evaluate loss and gradient for the three-layer convolutional network.

        Input / output: Same API as TwoLayerNet in fc_net.py.
        """
        W1, b1 = self.params["W1"], self.params["b1"]
        W2, b2 = self.params["W2"], self.params["b2"]
        W3, b3 = self.params["W3"], self.params["b3"]

        # pass conv_param to the forward pass for the convolutional layer
        # Padding and stride chosen to preserve the input spatial size
        filter_size = W1.shape[2]
        conv_param = {"stride": 1, "pad": (filter_size - 1) // 2}

        # pass pool_param to the forward pass for the max-pooling layer
        pool_param = {"pool_height": 2, "pool_width": 2, "stride": 2}

        scores = None
        ############################################################################
        # TODO: Implement the forward pass for the three-layer convolutional net,  #
        # computing the class scores for X and storing them in the scores          #
        # variable.                                                                #
        #                                                                          #
        # Remember you can use the functions defined in annp/fast_layers.py and  #
        # annp/layer_utils.py in your implementation (already imported).         #
        ############################################################################
        # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

        X, cache1 = conv_relu_pool_forward(X, W1, b1, conv_param, pool_param)
        X, cache2 = affine_relu_forward(X, W2, b2)
        scores, cache3 = affine_forward(X, W3, b3)

        # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
        ############################################################################
        #                             END OF YOUR CODE                             #
        ############################################################################

        if y is None:
            return scores

        loss, grads = 0, {}
        ############################################################################
        # TODO: Implement the backward pass for the three-layer convolutional net, #
        # storing the loss and gradients in the loss and grads variables. Compute  #
        # data loss using softmax, and make sure that grads[k] holds the gradients #
        # for self.params[k]. Don't forget to add L2 regularization!               #
        #                                                                          #
        # NOTE: To ensure that your implementation matches ours and you pass the   #
        # automated tests, make sure that your L2 regularization includes a factor #
        # of 0.5 to simplify the expression for the gradient.                      #
        ############################################################################
        # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

        loss, dX = softmax_loss(scores, y)
        loss += 0.5 * self.reg * (np.sum(np.square(W1)) + np.sum(np.square(W2)) + np.sum(np.square(W3)))

        dX, dW3, grads['b3'] = affine_backward(dX, cache3)
        dX, dW2, grads['b2'] = affine_relu_backward(dX, cache2)
        _, dW1, grads['b1'] = conv_relu_pool_backward(dX, cache1)
        grads['W1'] = dW1 + 2 * self.reg * W1
        grads['W2'] = dW2 + 2 * self.reg * W2
        grads['W3'] = dW3 + 2 * self.reg * W3

        # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
        ############################################################################
        #                             END OF YOUR CODE                             #
        ############################################################################

        return loss, grads

class AlternativeArchitecture(object):
    def __init__(
        self,
        conv_dims=((32, 7, 7, {"stride": 1, "pad": (7 - 1) // 2}, {"pool_height": 2, "pool_width": 2, "stride": 2}, None),),
        affine_dims=((100, None),),
        input_dim=(3, 32, 32),
        num_classes=10,
        reg=0.0,
        weight_scale=1e-2,
        dtype=np.float32,
    ):
        self.reg = reg
        self.dtype = dtype

        # conv
        # - x: Input data of shape (N, C, H, W)
        # - w: Filter weights of shape (F, C, HH, WW)
        # - b: Biases, of shape (F,)
        # - out: Output data, of shape (N, F, H', W') where H' and W' are given by
        #   H' = 1 + (H + 2 * pad - HH) / stride
        #   W' = 1 + (W + 2 * pad - WW) / stride
        # pool
        # - x: Input data, of shape (N, C, H, W)
        # - out: Output data, of shape (N, C, H', W') where H' and W' are given by
        #   H' = 1 + (H - pool_height) / stride
        #   W' = 1 + (W - pool_width) / stride
        # spatial bn
        # - gamma: Scale parameter, of shape (C,)
        # - beta: Shift parameter, of shape (C,)

        self.params = dict()
        self.conv_params = list()
        self.pool_params = list()
        self.spatial_bn_params = list()
        C, H, W = input_dim
        self.num_convs = 0
        for F, HH, WW, conv_param, pool_param, bn_param in conv_dims:
            self.params['conv_W' + str(self.num_convs)] = ((weight_scale * np.random.randn(F, C, HH, WW)).astype(dtype))
            self.params['conv_b' + str(self.num_convs)] = (np.zeros(F).astype(dtype))

            stride = conv_param['stride']
            pad = conv_param['pad']
            H = 1 + (H + 2 * pad - HH) // stride
            W = 1 + (W + 2 * pad - WW) // stride
            if pool_param is not None:
                stride = pool_param['stride']
                H = (H - pool_param['pool_height']) // stride + 1
                W = (W - pool_param['pool_width']) // stride + 1
                if bn_param is not None:
                    print("Warning! Pool and spatial bn aren't be valid at the same time! In this case, only pool is valid!")
            elif bn_param is not None:
                self.params['spatial_gamma' + str(self.num_convs)] = np.ones(F).astype(dtype)
                self.params['spatial_beta' + str(self.num_convs)] = np.zeros(F).astype(dtype)

            C = F
            self.num_convs += 1
            self.conv_params.append(conv_param)
            self.pool_params.append(pool_param)
            self.spatial_bn_params.append(bn_param)

        # affine
        # - w: A numpy array of weights, of shape (D, M)
        # - b: A numpy array of biases, of shape (M,)
        # bn
        # - gamma: Scale parameter of shape (D,)
        # - beta: Shift paremeter of shape (D,)

        self.bn_params = list()
        D = C * H * W
        self.num_affines = 0
        for M, bn_param in affine_dims:
            self.params['affine_W' + str(self.num_affines)] = (weight_scale * np.random.randn(D, M)).astype(dtype)
            self.params['affine_b' + str(self.num_affines)] = np.zeros(M).astype(dtype)
            if bn_param is not None:
                self.params['bn_gamma' + str(self.num_affines)] = np.ones(M).astype(dtype)
                self.params['bn_beta' + str(self.num_affines)] = np.zeros(M).astype(dtype)

            D = M
            self.num_affines += 1
            self.bn_params.append(bn_param)

        self.params['output_W'] = (weight_scale * np.random.randn(D, num_classes)).astype(dtype)
        self.params['output_b'] = np.zeros(num_classes).astype(dtype)

    def loss(self, X, y=None):
        X = X.astype(self.dtype)
        mode = "test" if y is None else "train"

        conv_caches = list()
        for i in range(self.num_convs):
            conv_param = self.conv_params[i]
            pool_param = self.pool_params[i]
            bn_param = self.spatial_bn_params[i]
            W = self.params['conv_W' + str(i)]
            b = self.params['conv_b' + str(i)]
            if pool_param is not None:
                X, conv_cache = conv_relu_pool_forward(X, W, b, conv_param, pool_param)
            elif bn_param is not None:
                gamma = self.params['spatial_gamma' + str(i)]
                beta = self.params['spatial_beta' + str(i)]
                bn_param['mode'] = mode
                X, conv_cache = conv_bn_relu_forward(X, W, b, gamma, beta, conv_param, bn_param)
            else:
                X, conv_cache = conv_relu_forward(X, W, b, conv_param)
            conv_caches.append(conv_cache)

        affine_caches = list()
        for i in range(self.num_affines):
            bn_param = self.bn_params[i]
            W = self.params['affine_W' + str(i)]
            b = self.params['affine_b' + str(i)]
            if bn_param is not None:
                gamma = self.params['bn_gamma' + str(i)]
                beta = self.params['bn_beta' + str(i)]
                bn_param['mode'] = mode
                X, cache = affine_bn_relu_forward(X, W, b, gamma, beta, bn_param)
            else:
                X, cache = affine_relu_forward(X, W, b)
            affine_caches.append(cache)

        W = self.params['output_W']
        b = self.params['output_b']
        scores, self.output_cache = affine_forward(X, W, b)

        # If test mode return early
        if mode == "test":
            return scores
        
        loss, dx = softmax_loss(scores, y)
        for i in range(self.num_convs):
            loss += 0.5 * self.reg * np.sum(np.square(self.params['conv_W' + str(i)]))
        for i in range(self.num_affines):
            loss += 0.5 * self.reg * np.sum(np.square(self.params['affine_W' + str(i)]))
        loss += 0.5 * self.reg * np.sum(np.square(self.params['output_W']))

        grads = dict()
        dx, grads['output_W'], grads['output_b'] = affine_backward(dx, self.output_cache)

        for i in range(self.num_affines - 1, -1, -1):
            cache = affine_caches[i]
            if self.bn_params[i] is not None:
                dx, dW, db, dgamma, dbeta = affine_bn_relu_backward(dx, cache)
                grads['bn_gamma' + str(i)] = dgamma
                grads['bn_beta' + str(i)] = dbeta
            else:
                dx, dW, db = affine_relu_backward(dx, cache)
            grads['affine_W' + str(i)] = (1 + self.reg) * dW
            grads['affine_b' + str(i)] = db

        for i in range(self.num_convs - 1, -1, -1):
            cache = conv_caches[i]
            if self.pool_params[i] is not None:
                dx, dW, db = conv_relu_pool_backward(dx, cache)
            elif self.spatial_bn_params[i] is not None:
                dx, dW, db, dgamma, dbeta = conv_bn_relu_backward(dx, cache)
                grads['spatial_gamma' + str(i)] = dgamma
                grads['spatial_beta' + str(i)] = dbeta
            else:
                dx, dW, db = conv_relu_backward(dx, cache)
            grads['conv_W' + str(i)] = (1 + self.reg) * dW
            grads['conv_b' + str(i)] = db

        return loss, grads
