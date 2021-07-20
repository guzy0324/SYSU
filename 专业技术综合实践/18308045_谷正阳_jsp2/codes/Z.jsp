<%@ page language="java" import="java.util.*,java.io.*" pageEncoding="utf-8" 
contentType="text/html;charset=utf-8"%>
<% 
	String course = (String)session.getAttribute("course");
	String id = session.getId();
%>
<!DOCTYPE  html>
<html  lang="zh-cn">
<head>
<title>Session Z</title>
</head>
<body>
  <h1>Session Z</h1> 
  session ID：<%=id%><br>
  course：<%=course%><br>
  <a href="X.jsp">X.jsp</a><br>
  <a href="Y.jsp">Y.jsp</a>
</body>
</html>
