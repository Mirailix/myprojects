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
    public partial class update_det : Form
    {
        private static string a, b, c, d,o;
        public update_det(Orders f1)
        {
            InitializeComponent();
            o = Convert.ToString(f1.dataGridView2.SelectedRows[0].Cells[0].Value);
            a = Convert.ToString(f1.dataGridView2.SelectedRows[0].Cells[2].Value);
            b = Convert.ToString(f1.dataGridView2.SelectedRows[0].Cells[3].Value);
            c = Convert.ToString(f1.dataGridView2.SelectedRows[0].Cells[4].Value);
        }

        private void update_det_Load(object sender, EventArgs e)
        {
            NpgsqlConnection con = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            DataSet ds = new DataSet();
            DataTable dt = new DataTable();
            NpgsqlDataAdapter da;

            string sql1 = "Select * from tovars";
            da = new NpgsqlDataAdapter(sql1, con);
            ds.Reset();
            da.Fill(ds);
            dt = ds.Tables[0];
            comboBox2.DataSource = dt;
            comboBox2.DisplayMember = "name";
            comboBox2.ValueMember = "id";

        }

        private void button1_Click(object sender, EventArgs e)
        {
            NpgsqlConnection con = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            con.Open();
            string sql1 = String.Format("update details set id_tovars={0},kolvo={1},price={2},dostavleno={3} where id_orders={4}", comboBox2.SelectedValue.ToString(),  a,b,c,o);
            NpgsqlCommand cmd = new NpgsqlCommand(sql1, con);
            cmd.ExecuteNonQuery();
        }
    }
}
