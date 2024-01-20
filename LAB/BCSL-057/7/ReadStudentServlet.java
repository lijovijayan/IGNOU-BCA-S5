import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

@WebServlet("/ReadStudentsServlet")
public class ReadStudentsServlet extends HttpServlet {

  private static final long serialVersionUID = 1L;

  protected void doGet(
    HttpServletRequest request,
    HttpServletResponse response
  ) throws IOException {
    response.setContentType("text/html;charset=UTF-8");
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
    } catch (ClassNotFoundException e) {}
    try (
      Connection connection = DriverManager.getConnection(
        "jdbc:mysql://localhost:3306/bcsl057_lab",
        "labuser",
        "password"
      )
    ) {
      String query = "SELECT * FROM students";
      try (
        PreparedStatement preparedStatement = connection.prepareStatement(
          query
        );
        ResultSet resultSet = preparedStatement.executeQuery()
      ) {
        PrintWriter out = response.getWriter();
        out.println(
          "<html><head><title>Student
Details</title></head><body><h2>Student Details:</h2><ul>"
        );
        while (resultSet.next()) {
          int rollnumber = resultSet.getInt("rollnumber");
          String stud_name = resultSet.getString("stud_name");
          String course = resultSet.getString("course");
          out.println(
            "<li>Name: " +
            stud_name +
            ", Roll Number: " +
            rollnumber +
            ", Course: " +
            course +
            "</li>"
          );
        }
        out.println("</ul>");
        out.println("</body>");
        out.println("</html>");
      }
    } catch (SQLException e) {}
  }
}
