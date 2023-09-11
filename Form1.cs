using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Npgsql;

namespace WindowsFormsApp4
{
    public partial class Form1 : Form
    {
        DataSet ds = new DataSet();
        DataTable dt = new DataTable();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            conn.Open();
            String sql = "Select * from tovars";
            NpgsqlDataAdapter da = new NpgsqlDataAdapter(sql, conn);
            ds.Reset();
            da.Fill(ds);
            dt = ds.Tables[0];
            dataGridView1.DataSource = dt.DefaultView;
            //dataGridView1.Columns[0].HeaderText = "имя";
            //dataGridView1.Columns[1].HeaderText = "адрес";
            //dataGridView1.Columns[2].HeaderText = "телефон";
            conn.Close();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Add newForm = new Add();
            newForm.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Update newForm = new Update(this);
            newForm.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int i = Int32.Parse(Convert.ToString(dataGridView1.SelectedRows[0].Cells[0].Value));
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            conn.Open();
            String sql = String.Format("delete from tovars where id={0}",i);
            NpgsqlCommand cmd = new NpgsqlCommand(sql, conn);
            cmd.ExecuteNonQuery();

            conn.Close();
        }
    }
}
