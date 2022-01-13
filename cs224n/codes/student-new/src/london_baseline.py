# Calculate the accuracy of a baseline that simply predicts "London" for every
#   example in the dev set.
# Hint: Make use of existing code.
# Your solution here should only be a few lines.
import utils

with open('birth_dev.tsv') as f:
    total, correct = utils.evaluate_places('birth_dev.tsv', ['London'] * len(f.readlines()))
print('Correct: {} out of {}: {}%'.format(correct, total, correct/total*100))
