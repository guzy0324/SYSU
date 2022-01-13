import math
import logging

import torch
import torch.nn as nn
from torch.nn import functional as F

logger = logging.getLogger(__name__)

class CausalSelfAttention(nn.Module):
    """
    A vanilla multi-head masked self-attention layer with a projection at the end.
    I believe I could have just used torch.nn.MultiheadAttention but their documentation
    is all but absent and code ugly so I don't trust it, rolling my own here.
    """

    def __init__(self, config):
        super().__init__()
        assert config.n_embd % config.n_head == 0
        # key, query, value projections for all heads
        self.key = nn.Linear(config.n_embd, config.n_embd)
        self.query = nn.Linear(config.n_embd, config.n_embd)
        self.value = nn.Linear(config.n_embd, config.n_embd)
        # regularization
        self.attn_drop = nn.Dropout(config.attn_pdrop)
        self.resid_drop = nn.Dropout(config.resid_pdrop)
        # output projection
        self.proj = nn.Linear(config.n_embd, config.n_embd)
        # causal mask to ensure that attention is only applied to the left in the input sequence
        self.register_buffer("mask", torch.tril(torch.ones(config.block_size, config.block_size))
                                     .view(1, 1, config.block_size, config.block_size))
        self.n_head = config.n_head

    def forward(self, x, layer_past=None):
        B, T, C = x.size()

        # calculate query, key, values for all heads in batch and move head forward to be the batch dim
        k = self.key(x).view(B, T, self.n_head, C // self.n_head).transpose(1, 2) # (B, nh, T, hs)
        q = self.query(x).view(B, T, self.n_head, C // self.n_head).transpose(1, 2) # (B, nh, T, hs)
        v = self.value(x).view(B, T, self.n_head, C // self.n_head).transpose(1, 2) # (B, nh, T, hs)

        # causal self-attention; Self-attend: (B, nh, T, hs) x (B, nh, hs, T) -> (B, nh, T, T)
        att = (q @ k.transpose(-2, -1)) * (1.0 / math.sqrt(k.size(-1)))
        att = att.masked_fill(self.mask[:,:,:T,:T] == 0, -1e10) # todo: just use float('-inf') instead?
        att = F.softmax(att, dim=-1)
        att = self.attn_drop(att)
        y = att @ v # (B, nh, T, T) x (B, nh, T, hs) -> (B, nh, T, hs)
        y = y.transpose(1, 2).contiguous().view(B, T, C) # re-assemble all head outputs side by side

        # output projection
        y = self.resid_drop(self.proj(y))
        return y

"""
Write your SynthesizerAttention below.
Hint: paste over the CausalSelfAttention above and modify it minimally.
"""

class SynthesizerAttention(nn.Module):
    def __init__(self, config):
        super().__init__()
        assert config.n_embd % config.n_head == 0
        # NEW learnable weights
        self.w1 = nn.Linear(config.n_embd, config.n_embd)
        self.w2 = nn.Parameter(torch.zeros(config.n_embd // config.n_head,
            config.block_size-1))
        self.b2 = nn.Parameter(torch.zeros(config.block_size-1))
        # value projection
        self.value = nn.Linear(config.n_embd, config.n_embd)
        # regularization
        self.attn_drop = nn.Dropout(config.attn_pdrop)
        self.resid_drop = nn.Dropout(config.resid_pdrop)
        # output projection
        self.proj = nn.Linear(config.n_embd, config.n_embd)
        # causal mask to ensure that attention is only applied to the left in
        #     the input sequence
        self.register_buffer("mask", torch.tril(
            torch.ones(config.block_size, config.block_size)).view(
                1, 1, config.block_size, config.block_size))
        self.n_head = config.n_head
        self.block_size = config.block_size

        nn.init.uniform_(self.w2,-0.001,0.001)

    def forward(self, x, layer_past=None):
        # TODO [part g]: Write your SynthesizerAttention below.
        #   Do not modify __init__().
        # Hints:
        #   - Paste over the CausalSelfAttention above and modify it minimally.
        #   - Consider especially the parameters self.w1, self.w2 and self.b2.
        #       How do these map to the matrices in the handout?

        # raise NotImplementedError
        B, T, _ = x.shape
        att = F.relu(self.w1(x)) # B x T x C
        att = att.reshape(B, T, self.n_head, -1) # B x T x nh x hs
        att = att @ self.w2 + self.b2 # B x T x nh x (BS - 1)
        att = att[:, :, :, :T] # B x T x nh x T
        att = self.attn_drop(F.softmax(att.permute(0, 2, 1, 3).masked_fill(self.mask[:,:,:T,:T] == 0, -1e10), dim=-1)) # B x nh x T x T
        v = self.value(x) # B x T x C
        v = v.reshape(B, T, self.n_head, -1) # B x T x nh x hs
        v = v.permute(0, 2, 1, 3) # B x nh x T x hs
        y = att @ v # B x nh x T x hs
        y = y.permute(0, 2, 1, 3) # B x T x nh x hs
        y = y.reshape(B, T, -1) # B x T x C
        return self.resid_drop(self.proj(y)) # B x T x C
