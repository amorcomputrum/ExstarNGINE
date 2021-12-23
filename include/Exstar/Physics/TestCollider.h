namespace exstar{
	struct TestCollider{
		int x,y,w,h;
		static bool CheckCollision(exstar::TestCollider t1,exstar::TestCollider t2);
	};
}