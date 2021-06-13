#ifndef SENSOR_HPP_
#define SENSOR_HPP_

using namespace std;

class memory
{
public:

	memory();
	~memory();
	uint8_t set_data2register(uint8_t addr, uint8_t* p_data, uint8_t size);
	void show_memory();
	uint8_t register_bank[200];
private:
	void flush_memory();
};

memory::memory()
{
	this->flush_memory();
}

memory::~memory()
{
}

void memory::flush_memory()
{
	for (uint32_t i = 0; i < 200; i++)
	{
		this->register_bank[i] = 0;
	}
}

uint8_t memory::set_data2register(uint8_t addr, uint8_t* p_data, uint8_t size)
{
	if (addr > 200 || (addr + size) > 200)
	{
		return -1;
	}

	while (size)
	{
		this->register_bank[addr++] = *p_data++;
		size--;
		p_data++;

	}
	return 0;
}

void memory::show_memory()
{
	for (int i = 0; i < 200; i++)
	{
		cout << "reg[" << i << "]: " << int(this->register_bank[i]) << "\n";
	}
}



class sensor : public memory
{
public:
	sensor();
	sensor(uint8_t addr);
	~sensor();
	void read(uint8_t register_addr, uint8_t* rx_buffer, uint8_t data_count);
	void write(uint8_t register_addr, uint8_t* tx_buffer, uint8_t data_count);
private:
	uint8_t slave_addr;
	void fill_mem_random();
};

sensor::sensor(uint8_t addr)
{
	this->slave_addr = addr;
	this->fill_mem_random();
}

sensor::~sensor()
{
}

void sensor::fill_mem_random()
{
	uint8_t r_number;

	for (uint8_t i = 0; i < 200; i++)
	{
		r_number = rand() % 256;
		this->register_bank[i] = r_number;
	}
}

void sensor::read(uint8_t register_addr, uint8_t* rx_buffer, uint8_t data_count)
{
	uint8_t i = 0;
	while (data_count)
	{
		rx_buffer[i] = this->register_bank[register_addr];
		register_addr++;
		i++;
		data_count--;
	}

}

void sensor::write(uint8_t register_addr, uint8_t* tx_buffer, uint8_t data_count)
{
	uint8_t i = 0;
	while (data_count)
	{
		this->register_bank[register_addr] = tx_buffer[i];
		i++;
		register_addr++;
		data_count--;
	}
}

#endif // !SENSOR_HPP_