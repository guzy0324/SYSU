# coding = utf-8
import time
import random
from selenium import webdriver
chrome_driver = "./chromedriver.exe"
browser = webdriver.Chrome(executable_path=chrome_driver)
url1 = 'https://cas.sysu.edu.cn/cas/login?service=https%3A%2F%2Fjwxt.sysu.edu.cn%2Fjwxt%2Fapi%2Fsso%2Fcas%2Flogin%3Fpattern%3Dstudent-login'
browser.get(url1)
name = browser.find_element_by_xpath('//*[@id="username"]')
name.click()
name.send_keys('改成自己的用户名')                                          #填用户名
pw = browser.find_element_by_xpath('//*[@id="password"]')
pw.click()
pw.send_keys('改成密码')                                                   #填密码
CAPTCHA = browser.find_element_by_xpath('//*[@id="captcha"]')
CAPTCHA.click()
captcha = input()
CAPTCHA.send_keys(captcha)
signin_btn = browser.find_element_by_xpath('//*[@id="fm1"]/section[2]/input[4]')
signin_btn.click()
names = ['课名1', '课名2']                                                 #填若干课名，保证搜索的时候不要有重的
is_reg = list()
for i in range(len(names)):
    is_reg.append(0)
url2 = 'https://jwxt.sysu.edu.cn/jwxt/mk/courseSelection/?resourceName=%25E9%2580%2589%25E8%25AF%25BE'
browser.get(url2)
num = len(names)
while 1:
    '''try:
    btn = browser.find_element_by_xpath('/html/body/div[7]/div/div[2]/div/div[2]/div/div/div[2]/button/span')
    btn.click()
    browser.get(url2)
except:
    pass'''
    browser.refresh()
    time.sleep(0.5)
    try:
        item = browser.find_element_by_xpath('//*[@id="root"]/div/div/div[2]/div/div[1]/div/div[2]/div[2]/div[2]/div/div[1]/div[1]/div[2]')
    except:
        continue
    item.click()
    search = browser.find_element_by_xpath('//*[@id="courseName"]')
    search_btn = browser.find_element_by_xpath('//*[@id="root"]/div/div/div[2]/div/div[1]/div/div[2]/div[2]/div[2]/div/div[2]/form/div[1]/div[1]/div[2]/div/span/span/button/div')
    for i in range(len(names)):
        if is_reg[i] == 0:
            try:
                search.clear()
                search.send_keys(names[i])
                search_btn.click()
                time.sleep(0.5)
            except:
                break
            try:
                reg = browser.find_element_by_xpath('//*[@id="root"]/div/div/div[2]/div/div[1]/div/div[2]/div[2]/div[2]/div/div[4]/div/ul/li/div[2]/div[9]/span')
                if reg.text == '选课':
                    reg.click()
                    time.sleep(0.5)
                    btn2 = browser.find_element_by_xpath('/html/body/div[6]/div/div[2]/div/div[1]/div/div/div[2]/button/span')
                    btn2.click()
                elif reg.text == '退课':
                    is_reg[i] = 1
                    num -= 1
            except:
                pass
    if num == 0:
        break
