using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ejercicio1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        { 
            DatosEstudiante.Class1 c1 = new DatosEstudiante.Class1();
            this.dataGridView1.DataSource = c1.estudiante().Tables[0];
        }

    }
}
