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
    public partial class Orders : Form
    {
        DataSet ds = new DataSet();
        DataTable dt = new DataTable();
        public Orders()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Add_order newForm = new Add_order();
            newForm.ShowDialog();
        }

        private void Orders_Load(object sender, EventArgs e)
        {
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            conn.Open();
            String sql = "Select * from orders";
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

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            DataGridViewSelectedRowCollection t = dataGridView1.SelectedRows;
            if (t.Count > 0)
            {
                DataGridViewRow row = t[0];
                string a = Convert.ToString(dataGridView1.SelectedRows[0].Cells[0].Value);
                //textBox1.Text = a;

                NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
                conn.Open();
                DataSet ds1 = new DataSet();
                DataTable dt1 = new DataTable();
                String sql = String.Format("Select * from details where id_orders ={0}", a);
                NpgsqlDataAdapter da1 = new NpgsqlDataAdapter(sql, conn);
                ds1.Reset();
                da1.Fill(ds1);
                dt1 = ds1.Tables[0];
                dataGridView2.DataSource = dt1.DefaultView;
                //dataGridView2.Columns[0].HeaderText = "id";
                //dataGridView2.Columns[1].HeaderText = "Дата";
                //dataGridView2.Columns[2].HeaderText = "id поставщика";
                //dataGridView2.Columns[3].HeaderText = "Общая сумма";
                conn.Close();
                textBox1.Text=Convert.ToString(dataGridView1.SelectedRows[0].Cells[2].Value);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Add_detail newForm = new Add_detail(this);
            newForm.ShowDialog();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int i = Int32.Parse(Convert.ToString(dataGridView1.SelectedRows[0].Cells[0].Value));
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            conn.Open();
            String sql = String.Format("delete from orders where id={0}", i);
            NpgsqlCommand cmd = new NpgsqlCommand(sql, conn);
            cmd.ExecuteNonQuery();

            conn.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int i = Int32.Parse(Convert.ToString(dataGridView2.SelectedRows[0].Cells[0].Value));
            int i2 = Int32.Parse(Convert.ToString(dataGridView2.SelectedRows[0].Cells[1].Value));
            NpgsqlConnection conn = new NpgsqlConnection("Server=localhost; Port=5432; User Id=postgres; Password=master1; Database=leha");
            conn.Open();
            String sql = String.Format("delete from details where id_orders={0} and id_tovars={1}", i,i2);
            NpgsqlCommand cmd = new NpgsqlCommand(sql, conn);
            cmd.ExecuteNonQuery();

            conn.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            update_order newForm = new update_order(this);
            newForm.ShowDialog();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            update_det newForm = new update_det(this);
            newForm.ShowDialog();
        }
    }
}
