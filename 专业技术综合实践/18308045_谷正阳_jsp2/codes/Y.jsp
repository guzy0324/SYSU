<%@ page language="java" import="java.util.*,java.io.*" pageEncoding="utf-8" 
contentType="text/html;charset=utf-8"%>
<% 
	String course = (String)session.getAttribute("course");
	String id = session.getId();
%>
<!DOCTYPE  html>
<html  lang="zh-cn">
<head>
<title>Session Y</title>
</head>
<body>
  <h1>Session Y</h1>
  session ID：<%=id%><br>
  course：<%=course%><br>
  <a href="X.jsp">X.jsp</a><br>
  <a href="Z.jsp">Z.jsp</a>
</body>
</html>
