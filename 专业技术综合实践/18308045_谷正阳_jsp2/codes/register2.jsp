<%@ page language="java" import="java.util.*" 
         contentType="text/html; charset=utf-8"%>
<%
    request.setCharacterEncoding("utf-8");
    if (request.getParameter("save") != null)
    {
        out.print("id：" + request.getParameter("id"));
        out.print("<br>同学名：" + request.getParameter("name"));
        out.print("<br>密码：" + request.getParameter("password"));
        out.print("<br>校区：" + request.getParameter("campus"));
        out.print("<br>年级：" + request.getParameter("grade"));
        out.print("<br>社团：[");
        String[] clubs = request.getParameterValues("club");
        for (int i = 0; i < clubs.length - 1; ++i)
        {
            out.print(clubs[i] + ',');
        }
        out.print(clubs[clubs.length - 1] + "]");
        out.print("<br>说明：" + request.getParameter("description"));
        out.print("<br>submit1：" + request.getParameter("save"));
        out.print("<br>submit2：" + request.getParameter("exit"));
    }
    if (request.getParameter("exit") != null)
    {
        response.sendRedirect("http://172.18.187.6/");
    }
%>
<!DOCTYPE HTML>
<html>
  <head>
    <title>用户注册输入显示</title>
  </head>  
  <body>

  </body>
</html>
