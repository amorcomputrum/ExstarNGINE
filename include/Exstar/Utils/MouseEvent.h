namespace exstar{
	struct MouseEvent{
		enum Button{
			Left=0,Right=1,Middle=2,Four=3,Five=4,Six=5,Seven=6,Eight=7
		};
		int button;
		Point pos;
	};
}