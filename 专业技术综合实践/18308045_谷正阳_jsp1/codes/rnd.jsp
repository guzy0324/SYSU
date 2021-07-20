<%@ page language="java" import="java.util.Random" contentType="text/html;charset=UTF-8" %>
<html>
    <head>
        <title>40个随机数</title>
    </head>
    <body>
        <h1>40个随机数</h1>
        <%Random rnd = new Random(50);
        for (int i = 0; i < 40; ++i)
        {%>
        <span><%=rnd.nextInt(1000)%></span>
        <%}%>
    </body>
</html>
