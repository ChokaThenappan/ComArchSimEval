class jmpp : public FjK
{
    private:
	string	_label;

    public:
	jmpp(u08 j, string L) : FjK(0x34, j, 0) { _label = L; }

	bool execute()
	{
	    if (0 < PROC.X(_j).i()) return true;
            else return false;
	}

	string mnemonic() const
	{
	    return "jmpp";
	}

	bool ops()
	{
	    process(new operations::cmpz(_j));
	    process(new operations::jmpp());
	    return false;
	}

	void fixit()
	{
	    assert(label2line.count(_label));
	    u32 targetline = label2line[_label];
	    assert(line2addr.count(targetline));
	    u32 targetaddr = line2addr[targetline];
	    assert(line2addr.count(_line));
	    u32 sourceaddr = line2addr[_line];
	    _K = ((targetaddr/8) - (sourceaddr/8)) & 0xfffff;
	}
};