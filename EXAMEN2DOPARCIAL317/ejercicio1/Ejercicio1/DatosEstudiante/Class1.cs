using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;

namespace DatosEstudiante
{
    public class Class1
    {
        public DataSet estudiante()
        {
            SqlConnection conectar = new SqlConnection();
            conectar.ConnectionString = "server=(local);user=sa;pwd=dokimaniacos;database=school";
            SqlDataAdapter ada = new SqlDataAdapter();
            ada.SelectCommand = new SqlCommand();
            ada.SelectCommand.Connection = conectar;
            ada.SelectCommand.CommandText = "SELECT * FROM estudiante";
            DataSet ds = new DataSet();
            ada.Fill(ds);
            return ds;
        }
    }
}
