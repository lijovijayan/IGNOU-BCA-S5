import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

@WebServlet("/CurrentDateServlet")
public class CurrentDateServlet extends HttpServlet {

  private static final long serialVersionUID = 1L;

  protected void doGet(
    HttpServletRequest request,
    HttpServletResponse response
  ) throws IOException {
    response.setContentType("text/html;charset=UTF-8");
    PrintWriter out = response.getWriter();
    out.println("<html>");
    out.println("<head>");
    out.println("<title>Current Date & Time</title>");
    out.println("</head>");
    out.println("<body>");
    out.println("<h2>Current Date & Time:</h2>");
    // Get the current date and format it
    SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd
HH:mm:ss");
    String currentDate = dateFormat.format(new Date());
    out.println("<p>" + currentDate + "</p>");
    out.println("</body>");
    out.println("</html>");
  }
}
