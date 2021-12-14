namespace exstar{
	/**
	 * MouseEvent is a struct that stores what button was used and where it happened
	*/
	struct MouseEvent{
		enum Button{
			Left=0,Right=1,Middle=2,Four=3,Five=4,Six=5,Seven=6,Eight=7
		};
		/**
		 * The button that was used
		*/
		int button;
		/**
		 * The position that it happened
		*/
		Point pos;
	};
}