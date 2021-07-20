<%@ page language="java" import="java.util.*,java.io.*" pageEncoding="utf-8" 
contentType="text/html;charset=utf-8"%>
<% 
	session.setAttribute("course", "移动Web应用设计" + " --- " + new Date());
	String id = session.getId();
%>
<!DOCTYPE  html>
<html  lang="zh-cn">
<head>
<title>Session X</title>
</head>
<body>
  <h1>Session X</h1>  
  session ID：<%=id%><br>
  <a href="Y.jsp">Y.jsp</a><br>
  <a href="Z.jsp">Z.jsp</a>
</body>
</html>
