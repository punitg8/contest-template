//Adding segment tree part in the code
//Seg - basically vector of size 4*N and ind initially is 0 basically poiniting to curr root
void build(ll ind,ll low,ll high,vector<ll> &seg,vector<ll> &a){
    if(low==high){
        seg[ind] = a[low];
        return;
    }
    ll mid=(high-low)/2+low;
    build(2*ind+1,low,mid,seg,a); //Left child build kar re hai
    build(2*ind+2,mid+1,high,seg,a); //Right child build kar re hai 
    seg[ind]=seg[2*ind+1]+seg[2*ind+2]; //max rakh re as segment tree for max hai ye
}

//Now to perform range query of max
//ind - curr root , low - curr low, high - curr high , l - given low of range , r - given high of range
ll query(ll ind,ll low,ll high,ll l,ll r,vector<ll> &seg){
    if(low>=l&&r>=high){
        return seg[ind]; // complete overlap wala case
    }
    if(low>r||high<l){
        return 0; //Bilkul bhi overlap ni wala case isliye sum = 0
    }
    ll mid=(high-low)/2+low;
    //Overlap wale case mein dono side jayenge abb
    ll left = query(2*ind+1,low,mid,l,r,seg);
    ll right = query(2*ind+2,mid+1,high,l,r,seg);
    return left+ right;
}

//Point update queries ye O(log(n)) legi 
void pointUpdate(ll ind,ll low,ll high,ll point,ll val,vector<ll> &seg){
    if(low==high){
        seg[ind]+=val; //incase us point ko val se increment karna hai to +=val karta
    }else{
        ll mid=(high-low)/2+low;
        if(point<=mid) pointUpdate(2*ind+1,low,mid,point,val,seg);
        else pointUpdate(2*ind+2,mid+1,high,point,val,seg);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
} 

//Lazy update for range and query this part is taken from code snippet
void rangeUpdate(ll ind, ll left, ll right, ll l, ll r, ll val,vector<ll> &seg,vector<ll> &lazy){
    if(lazy[ind]){
        seg[ind] = (right-left+1) * lazy[ind];
        if(left!=right){
            lazy[2*ind+1] += lazy[ind]; 
            lazy[2*ind+2] += lazy[ind]; 
        }
        lazy[ind] = 0;
    }

    // If range is completely outside...
    if(r < left || right < l || left > right) return ;

    // If range is completely inside...
    if(left>=l && right<=r){
        seg[ind] += (right-left+1)*val;
        if(left!=right){
            lazy[2*ind+1] += val;
            lazy[2*ind+2] += val;
        }
        return ;
    }

    // If range is partially inside or partially outside...
    ll mid = (left + right) / 2;
    rangeUpdate(2*ind+1, left, mid, l, r, val,seg,lazy);
    rangeUpdate(2*ind+2, mid+1, right, l, r, val,seg,lazy);
    seg[ind] = seg[ind*2+1] + seg[ind*2+2];
}
ll querySumLazy(ll ind, ll left, ll right, ll l, ll r,vector<ll> &seg,vector<ll> &lazy){
    if(lazy[ind]){
        seg[ind] += (right - left + 1) * lazy[ind];
        if(left!=right){
            lazy[2*ind+1] += lazy[ind];
            lazy[2*ind+2] += lazy[ind];
        }
        lazy[ind] = 0;
    }

    // If range is completely outside...
    if(r < left || right < l || left > right) return 0;

    // If range is completely inside...
    if(left >= l && right <= r){
        return seg[ind];
    }

    // If range is partially inside or partially outside...
    ll mid = (right + left)/2;
    ll leftSide = querySumLazy(2*ind+1, left, mid, l, r,seg,lazy);
    ll rightSide = querySumLazy(2*ind+2, mid+1, right, l, r,seg,lazy);
    return leftSide + rightSide;
}
