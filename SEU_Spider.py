#coding:utf-8
__author__ = 'LQ'
import urllib
import urllib2
import cookielib
import re
import getpass

class SEU:
    def __init__(self,uname,upwd):
        self.headers ={'User-Agent':'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)',
                       'Referer':'http://202.119.4.150/nstudent/login.aspx'}

        #第一个用于登录
        #第二个用于成绩查询
        self.loginUrl="http://202.119.4.150/nstudent/login.aspx"
        self.gradeUrl="http://202.119.4.150/nstudent/grgl/xskccjcx.aspx"
        #进行cookie登录
        #下面这个不知道什么东西的,也特么要POST发送,而且好像每次都一样
        vistate='dDw2Nzg5Mjk2NTY7dDw7bDxpPDE+Oz47bDx0PD' \
                'tsPGk8MT47aTwzPjs+O2w8dDxwPGw8VmlzaWJsZ' \
                'Ts+O2w8bzx0Pjs+Pjs7Pjt0PHA8bDxWaXNpYmxl' \
                'Oz47bDxvPGY+Oz4+O2w8aTw1Pjs+O2w8dDxwPHA8b' \
                'DxUZXh0Oz47bDzmnpfmuIU7Pj47Pjs7Pjs+Pjs+Pjs' \
                '+PjtsPG9rOz4+6tpmUm+JK+RXWrJOIE2R4/QF4zg='
        self.postdata=urllib.urlencode({"__VIEWSTATE":vistate,'txt_user':uname,'txt_password':upwd,'ok.x':'31','ok.y':'9'})
        #建立cookie的opener
        self.cookies=cookielib.CookieJar()
        self.opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(self.cookies))

    def login(self):
        #登录
        request=urllib2.Request(
            url=self.loginUrl,
            data=self.postdata,
            headers=self.headers
        )
        result=self.opener.open(request)

    def getgrade(self):
        result=self.opener.open(self.gradeUrl)
        pattern='<td>(.*?)</td><td>(.*?)</td><td>(.*?)</td><td>(.*?)</td><td>(.*?)</td>'
        pattern=re.compile(pattern,re.S)
        items=re.findall(pattern,result.read())
        for item in items:
            if item[0]!='课程':
                print "%10s%10s%10s   %s"%(item[1],item[3],item[4],item[0].decode('utf-8').encode('gb2312'))
if __name__=="__main__":
    uname=raw_input("请输入用户名: ".decode('utf-8').encode('gb2312'))
    pwd=raw_input("请输入密码: ".decode('utf-8').encode('gb2312'))
    seu=SEU(uname,pwd)
    seu.login()
    seu.getgrade()
    a=raw_input("按回车退出!".decode('utf-8').encode('gb2312'))