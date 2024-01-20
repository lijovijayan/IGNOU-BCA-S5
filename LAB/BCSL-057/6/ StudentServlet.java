import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/StudentServlet")
public class StudentServlet extends HttpServlet {

  private static final long serialVersionUID = 1L;

  @Override
  protected void doGet(
    HttpServletRequest request,
    HttpServletResponse response
  ) throws IOException {
    processRequest(request, response);
  }

  @Override
  protected void doPost(
    HttpServletRequest request,
    HttpServletResponse response
  ) throws IOException {
    processRequest(request, response);
  }

  private void processRequest(
    HttpServletRequest request,
    HttpServletResponse response
  ) throws IOException {
    response.setContentType("text/html;charset=UTF-8");
    String firstName = request.getParameter("firstName");
    String lastName = request.getParameter("lastName");
    String firstNamePost = request.getParameter("firstNamePost");
    String lastNamePost = request.getParameter("lastNamePost");
    PrintWriter out = response.getWriter();
    out.println("<html>");
    out.println("<head>");
    out.println("<title>Form Data</title>");
    out.println("</head>");
    out.println("<body>");
    out.println("<h2>Form Data Submitted:</h2>");
    if (firstName != null && lastName != null) {
      out.println("<p>First Name (GET): " + firstName + "</p>");
      out.println("<p>Last Name (GET): " + lastName + "</p>");
    }
    if (firstNamePost != null && lastNamePost != null) {
      out.println("<p>First Name (POST): " + firstNamePost + "</p>");
      out.println("<p>Last Name (POST): " + lastNamePost + "</p>");
    }
    out.println("</body>");
    out.println("</html>");
  }
}
