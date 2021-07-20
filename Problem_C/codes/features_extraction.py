# -*- coding:utf-8 -*
import openpyxl
def readxl():
    data_str = str()
    data_list = list()
    for file in ('hair_dryer', 'microwave', 'pacifier'):
        data = list()
        book = openpyxl.load_workbook('../data/' + file + '.xlsx')
        sheet = book[file]
        
        for i in sheet.rows:
            #rate = i[7].value
            title = str(i[12].value)
            review = str(i[13].value)
            data_str += title + '. ' + review + '. '
            data.append(title + '. ' + review + '. ')
        data_list.append(data)
    return data_str, data_list

from nltk import word_tokenize, pos_tag, WordNetLemmatizer
def generate_word_list(data):
    pt = pos_tag(word_tokenize(data))
    wnl = WordNetLemmatizer()
    word_list = list()
    for word, tag in pt:
        word = word.lower()
        if tag.startswith('NN'):
            word_list.append(wnl.lemmatize(word, pos='n'))
        elif tag.startswith('VB'):
            word_list.append(wnl.lemmatize(word, pos='v'))
        elif tag.startswith('JJ'):
            word_list.append(wnl.lemmatize(word, pos='a'))
        elif tag.startswith('R'):
            word_list.append(wnl.lemmatize(word, pos='r'))
    return word_list

def count_word_list(data, word_list):
    pt = pos_tag(word_tokenize(data))
    wnl = WordNetLemmatizer()
    vec = [0] * len(word_list)
    for word, tag in pt:
        word = word.lower()
        if tag.startswith('NN'):
            pos = 'n'
        elif tag.startswith('VB'):
            pos = 'v'
        elif tag.startswith('JJ'):
            pos = 'a'
        elif tag.startswith('R'):
            pos = 'r'
        else:
            continue
        lemma = wnl.lemmatize(word, pos=pos)
        for i in range(len(word_list)):
            if lemma == word_list[i]:
                vec[i] += 1
    return vec

from nltk import FreqDist
def stat(word_list):
    freq = FreqDist(word_list)
    return freq

from matplotlib import pyplot, rcParams
def plot_bar(stat_list):
    rcParams["font.size"] = 5

    word_list = list()
    freq_list = list()
    for (word, frequency) in stat_list:
        word_list.append(word)
        freq_list.append(frequency)
    x = range(len(freq_list))
    y = max(freq_list)
    """
    绘制条形图
    left:长条形中点横坐标
    height:长条形高度
    width:长条形宽度，默认值0.8
    label:为后面设置legend准备
    """
    
    rects1 = pyplot.bar(word_list, freq_list, width=0.4, alpha=0.8, color='red', label="Frequency statistics")
    pyplot.ylim(0, y)     # y轴取值范围
    pyplot.ylabel("Frequency")
    
    """
    设置x轴刻度显示值
    参数一：中点坐标
    参数二：显示值
    """
    
    pyplot.xticks([index + 0.2 for index in x], word_list)
    pyplot.xlabel("Word")  
    pyplot.title("")
    pyplot.legend()     # 设置题注
    
    # 编辑文本
    for rect in rects1:
        height = rect.get_height()
        pyplot.text(rect.get_x() + rect.get_width() / 2, height, str(height), ha="center", va="bottom")
    pyplot.title("")
    pyplot.legend()
    pyplot.show()
'''
data_str, data_list = readxl()
word_list = generate_word_list(data_str)
freq = stat(word_list)
plot_bar(freq.most_common(20))'''

'''
word_list = ['love', 'great', 'good', 'nice', 'best', 'bad', 'issue', 'noisy', 'be', 'have', 'do', 'i']
vec_list_list = list()
for data in data_list:
    vec_list = list()
    for record in data:
        vec_list.append(count_word_list(record, word_list))
    vec_list_list.append(vec_list)'''
'''
import json
with open("../data/vec.txt", 'w') as f:
    f.write(json.dumps(vec_list_list, indent = 4))
'''
'''
for i in range(3):
    with open("../data/vec" + str(i) + ".txt", "a+") as f:
        for vec in vec_list_list[i]:
            for ele in vec:
                f.write(str(ele) + "\t")
            f.write("\n")'''
def read_tfidf():
    book = openpyxl.load_workbook('../data/tfidf.xlsx')
    sheet = book["Sheet1"]
    vec1 = list()
    vec2 = list()
    rate = list()
    for i in sheet.rows:
        vec1.append([x.value for x in i[0:8]])
        vec2.append([x.value for x in i[8:12]])
        rate.append(i[12].value)
    return vec1, vec2, rate

import numpy
from sklearn.feature_extraction.text import CountVectorizer  # 从sklearn.feature_extraction.text里导入文本特征向量化模块
def train(X_train, y_train):
    #3.使用朴素贝叶斯进行训练
    mnb = MultinomialNB()   # 使用默认配置初始化朴素贝叶斯
    mnb.fit(X_train,y_train)    # 利用训练数据对模型参数进行估计
    return mnb

def predict(mnb, X_test):
    y_predict = mnb.predict(X_test)     # 对参数进行预测
    return y_predict

'''
vect1 = list()
vect2 = list()
for i in vec1:
    t1 = numpy.array([int(x * 10**18) for x in i])
    t1.astype("int")
    t2 = numpy.array([int(x * 10**18) for x in i])
    t2.astype("int")
    vect1.append(t1)
    vect2.append(t2)
vect1 = numpy.array(vect1)
vect2 = numpy.array(vect2)
ratet = numpy.array(rate)
ratet.astype("int")
mnb = train(vect1[:boundary], ratet[:boundary])
'''