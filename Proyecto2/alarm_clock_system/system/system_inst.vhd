	component system is
		port (
			clk_clk       : in  std_logic                    := 'X';             -- clk
			h_1_export    : out std_logic_vector(3 downto 0);                    -- export
			h_2_export    : out std_logic_vector(3 downto 0);                    -- export
			m_1_export    : out std_logic_vector(3 downto 0);                    -- export
			m_2_export    : out std_logic_vector(3 downto 0);                    -- export
			reset_reset_n : in  std_logic                    := 'X';             -- reset_n
			s_1_export    : out std_logic_vector(3 downto 0);                    -- export
			s_2_export    : out std_logic_vector(3 downto 0);                    -- export
			set_export    : in  std_logic_vector(4 downto 0) := (others => 'X')  -- export
		);
	end component system;

	u0 : component system
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --   clk.clk
			h_1_export    => CONNECTED_TO_h_1_export,    --   h_1.export
			h_2_export    => CONNECTED_TO_h_2_export,    --   h_2.export
			m_1_export    => CONNECTED_TO_m_1_export,    --   m_1.export
			m_2_export    => CONNECTED_TO_m_2_export,    --   m_2.export
			reset_reset_n => CONNECTED_TO_reset_reset_n, -- reset.reset_n
			s_1_export    => CONNECTED_TO_s_1_export,    --   s_1.export
			s_2_export    => CONNECTED_TO_s_2_export,    --   s_2.export
			set_export    => CONNECTED_TO_set_export     --   set.export
		);

