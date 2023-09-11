using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp4
{
    public partial class menu : Form
    {
        public menu()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 newForm = new Form1();
            newForm.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Client newForm = new Client();
            newForm.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Orders newForm = new Orders();
            newForm.ShowDialog();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            otchet newForm = new otchet();
            newForm.ShowDialog();
        }
    }
}
