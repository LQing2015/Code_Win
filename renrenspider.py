#coding:utf-8
__author__ = 'LQ'

import urllib2,urllib
import sys,re
import cookielib
import time
import gzip
import StringIO
from BeautifulSoup import BeautifulSoup

import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )

class RenRen:
    def __init__(self,uname,upwd):
         self.friend={}
         self.ID=""
         self.uname=uname
         self.upwd=upwd
         self.agent ='Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
         self.opener=urllib2.build_opener(urllib2.HTTPCookieProcessor(cookielib.CookieJar()))
    def login(self):
        loginUrl="http://www.renren.com/PLogin.do"
        postdata=urllib.urlencode({"email":self.uname,"password":self.upwd})
        headers={"User-Agent":self.agent,'Referer':'http://www.renren.com/'}
        req=urllib2.Request(url=loginUrl,data=postdata,headers=headers)
        r=self.opener.open(req)
        strPattern=r"""nx.user.*?id : "(\d*?)".*?requestToken : '(.*?)'.*?_rtk : '(.*?)'"""
        pattern=re.compile(strPattern,re.S)
        m=pattern.search(r.read())
        self.ID= m.group(1)
        self.requestToken=m.group(2)
        self.rtk=m.group(3)
    def pushStatus(self,content):
        url=r"http://shell.renren.com/"+self.ID+r'/status'
        data={"channel":"renren",
              "content":content,
              "requestToken":self.requestToken,
              "_rtk":self.rtk}
        headers ={'User-Agent':self.agent,'Referer':'http://shell.renren.com/ajaxproxy.htm'}
        data=urllib.urlencode(data)
        req=urllib2.Request(url=url,data=data)
        self.opener.open(req)
    def GetFriend(self):
        url=r"http://friend.renren.com/groupsdata"
        req=urllib2.Request(url)
        r=self.opener.open(req)
        strP=r'\{"fid":(.*?),"timepos":.*?,"fgroups":\[".*?"\],"comf":.*?,"compos":.*?,"large_url":".*?","tiny_url":".*?","fname":"(.*?)".*?"pos":.*?\}'
        file_content=r.read()
        Pattern=re.compile(strP,re.S)
        friends=re.findall(Pattern,file_content)
        frienddict={}
        for friend in friends:
            frienddict[friend[0]]=friend[1]
        self.friend=frienddict
    def GetALLStatusId(self,id):
        page=0
        AllStatusID=[]
        while True:
            data={'userId':id,'curpage':page,'requestToken':self.requestToken,'_rtk':self.rtk}
            params=urllib.urlencode(data)
            url='http://status.renren.com/GetSomeomeDoingList.do?%s'%params
            req=urllib2.Request(url)
            r=self.opener.open(req)
            str_pattern=r'likeMap.*?\{(.*?)\}.*?headurl'
            pattern=re.compile(str_pattern,re.S)
            status_num=pattern.search(r.read())
            if status_num is not None:
                curList=re.findall(r'"status_([0-9]*?)"',status_num.group(0))
                if len(curList)==0:
                    break
                else:
                    AllStatusID+=curList
            else:
                break
            page+=1
        return AllStatusID
    def SoupStatus(self,doc):
        soup = BeautifulSoup(doc)
        status_trans=soup.find(attrs={'class':'status-detail-artical'})
        status_origin=soup.find(attrs={'class':'status-share-origin'})
        status_time=soup.find(attrs={'class':'detail-release-time'})
        s_str=''
        for status in (status_time,status_trans,status_origin):
            if status is None:
                continue
            for s in status.contents:
                if isinstance(s,type(status)):
                    s_str+=s.text
                else:
                    s_str+=s
        return s_str
    def DownLoadStatus(self,Id):
        if Id not in self.friend:
            return
        file=open(Id+".txt",'w')
        statusList=self.GetALLStatusId(Id)
        baseurl=r"http://status.renren.com/status/v7/"+Id+"/"
        split="\n"+"*"*300+"\n"
        for statusid in statusList:
            url=baseurl+statusid
            req=urllib2.Request(url)
            r=self.opener.open(req)
            status=self.SoupStatus(r.read())
            file.write(status.decode('utf-8'))
            file.write(split)
            print "Finished Status: "+statusid
        file.close()
        print "Download status finished!!"


if __name__=="__main__":
    renren=RenRen("15651620957","linqing0821")
    renren.login()
    renren.GetFriend()
    for ID in renren.friend.keys():
        renren.DownLoadStatus(ID)